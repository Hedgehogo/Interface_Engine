#pragma once

#include "../baseButton.hpp"

namespace ui {
	class Button : public BaseButton {
	public:
		Button(IScalable* background, int interaction);
		
		Button(IScalable* background, IInteraction* interaction);
		
		void init(InteractiveInitInfo interactiveInitInfo) override;
		
		Button* copy() override;
	
	protected:
		int interactionIndex;
	};
	
	template<>
	struct DecodePointer<Button> {
		static bool decodePointer(const YAML::Node& node, Button*& button);
	};
}
