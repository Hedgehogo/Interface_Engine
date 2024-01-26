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
			
			Button* make(InitInfo init_info) override;
		};
		
		Button(Make&& make, InitInfo init_info);
		
		Button(BoxPtr<IScalable>&& background, BoxPtr<IBaseInteraction>&& interaction);
		
		void init(InitInfo init_info) override;
		
		void update() override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		Button* copy() override;
	
	protected:
		InteractiveData interactive_;
	};
	
}

template<>
struct ieml::Decode<char, ie::Button::Make> {
	static orl::Option<ie::Button::Make> decode(ieml::Node const& node);
};
