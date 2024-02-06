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
				const sf::String& text,
				const orl::Option<sf::Color>& text_color = {},
				const orl::Option<sf::Font&>& font = {},
				const orl::Option<sf::Text::Style>& style = {},
				std::vector<BoxPtr<BaseLine::Make>>&& lines = {},
				const orl::Option<size_t>& size = {},
				const orl::Option<sf::Color>& text_selection_color = {},
				const orl::Option<sf::Color>& background_selection_color = {},
				const orl::Option<sf::Color>& inactive_text_selection_color = {},
				const orl::Option<sf::Color>& inactive_background_selection_color = {}
			);
			
			InteractiveTextBlock* make(TextBockInitInfo init_info) override;
		};
		
		InteractiveTextBlock(Make&& make, TextBockInitInfo init_info);
		
		bool in(sf::Vector2f mouse_position) override;
		
		void update() override;
		
		bool update_interactions(sf::Vector2f) override;
	
	protected:
		InteractionManager* interaction_manager;
		
		bool interact;
		bool old_interact;
		
		BoxPtr<IInteraction> interaction;
	};
}

template<>
struct ieml::Decode<char, ie::InteractiveTextBlock::Make> {
	static orl::Option<ie::InteractiveTextBlock::Make> decode(ieml::Node const& node);
};