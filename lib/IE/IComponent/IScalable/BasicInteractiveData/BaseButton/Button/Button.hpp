#pragma once

#include "../BaseButton.hpp"

namespace ie {
	class Button : public BaseButton {
	public:
		struct Make : public virtual IScalableObject::Make {
			BoxPtr<IScalable::Make> background;
			BoxPtr<IBaseInteraction::Make> interaction;
			
			Make(BoxPtr<IScalable::Make>&& background, BoxPtr<IBaseInteraction::Make>&& interaction);
			
			Button* make(InitInfo initInfo) override;
		};
		
		Button(Make&& make, InitInfo initInfo);
		
		Button(BoxPtr<IScalable>&& background, BoxPtr<IBaseInteraction>&& interaction);
		
		void init(InitInfo initInfo) override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		Button* copy() override;
	
	protected:
		InteractiveData interactive;
	};
	
	template<>
	struct DecodePointer<Button> {
		static bool decodePointer(const YAML::Node& node, Button*& button);
	};
}
