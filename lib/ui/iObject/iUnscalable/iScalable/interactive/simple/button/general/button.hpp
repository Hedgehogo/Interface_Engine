#pragma once

#include "../baseButton.hpp"

namespace ui {
	class Button : public BaseButton {
	protected:
		int interactionIndex;
	
	public:
		Button(IScalable* background, int interaction);
		
		Button(IScalable* background, IInteraction* interaction);
		
		void init(InteractiveInitInfo interactiveInitInfo) override;
		
		Button* copy() override;
	};
	
	template<>
	struct DecodePointer<Button> {
		static bool decodePointer(const YAML::Node& node, Button*& button);
	};
}
