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
				Indexed<TextStyle>&& text_style
			);
			
			auto make(TextBockInitInfo init_info) -> InteractiveTextBlock* override;
		};
		
		InteractiveTextBlock(Make&& make, TextBockInitInfo init_info);
		
		auto in(sf::Vector2f point_position) -> bool override;
		
		auto update() -> void override;
		
		auto handle_event(Event) -> bool override;
	
	protected:
		InteractionManager* interaction_manager_;
		BoxPtr<IInteraction> interaction_;
	};
}

template<>
struct ieml::Decode<char, ie::InteractiveTextBlock::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::InteractiveTextBlock::Make>;
};