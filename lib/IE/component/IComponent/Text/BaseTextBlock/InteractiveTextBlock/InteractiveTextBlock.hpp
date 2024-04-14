#pragma once

#include "../TextBlock/TextBlock.hpp"
#include "IE/interaction/IInteraction/IInteraction.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	class InteractiveTextBlock : public TextBlock {
	public:
		struct Make : public TextBlock::Make {
			BoxPtr<IBaseInteraction::Make> interaction;
			
			Make(
				BoxPtr<IBaseInteraction::Make>&& interaction,
				sf::String const& text,
				orl::Option<sf::Color> text_color = {},
				orl::Option<sf::Font&> font = {},
				orl::Option<sf::Text::Style> style = {},
				std::vector<BoxPtr<BaseLine::Make> >&& lines = {},
				orl::Option<size_t> size = {},
				orl::Option<sf::Color> text_selection_color = {},
				orl::Option<sf::Color> background_selection_color = {},
				orl::Option<sf::Color> inactive_text_selection_color = {},
				orl::Option<sf::Color> inactive_background_selection_color = {}
			);
			
			auto make(TextBockInitInfo init_info) -> InteractiveTextBlock* override;
		};
		
		InteractiveTextBlock(Make&& make, TextBockInitInfo init_info);
		
		auto in(sf::Vector2f point_position) -> bool override;
		
		auto update() -> void override;
		
		auto update_interactions(Event) -> bool override;
	
	protected:
		InteractionManager* interaction_manager_;
		
		bool interact_;
		bool old_interact_;
		
		BoxPtr<IInteraction> interaction_;
	};
}

template<>
struct ieml::Decode<char, ie::InteractiveTextBlock::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::InteractiveTextBlock::Make>;
};