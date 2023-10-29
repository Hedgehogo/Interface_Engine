#pragma once

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
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<Button> {
		static bool decode_pointer(const YAML::Node& node, Button*& button);
	};
	*/
}
