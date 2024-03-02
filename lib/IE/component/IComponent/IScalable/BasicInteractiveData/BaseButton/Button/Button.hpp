#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../BaseButton.hpp"

namespace ie {
	class Button : public BaseButton {
	public:
		struct Make : public virtual IScalableObject::Make {
			BoxPtr<IScalable::Make> background;
			BoxPtr<IBaseInteraction::Make> interaction;
			
			Make(BoxPtr<IScalable::Make>&& background, BoxPtr<IBaseInteraction::Make>&& interaction);
			
			auto make(InitInfo init_info) -> Button* override;
		};
		
		Button(Make&& make, InitInfo init_info);
		
		auto update() -> void override;
		
		auto update_interactions(sf::Vector2f mouse_position) -> bool override;
		
	protected:
		InteractiveData interactive_;
	};
}

template<>
struct ieml::Decode<char, ie::Button::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Button::Make>;
};
