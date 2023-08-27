#pragma once

#include "../BasicBaseButton.hpp"

namespace ie {
	class Button : public BaseButton {
	public:
		struct Make : public IScalable::Make {
			BoxPtr<IScalable::Make> background;
			BoxPtr<IBaseInteraction> interaction;
			
			Make(BoxPtr<IScalable::Make>&& background, BoxPtr<IBaseInteraction>&& interaction);
			
			Button* make(InitInfo initInfo) override;
		};
		
		Button(Make&& make, InitInfo initInfo);
		
		Button(BoxPtr<IScalable>&& background, BoxPtr<IBaseInteraction>&& interaction);
		
		void init(InitInfo initInfo) override;
		
		Button* copy() override;
	
	protected:
		std::size_t interactionIndex;
	};
	
	template<>
	struct DecodePointer<Button> {
		static bool decodePointer(const YAML::Node& node, Button*& button);
	};
}
