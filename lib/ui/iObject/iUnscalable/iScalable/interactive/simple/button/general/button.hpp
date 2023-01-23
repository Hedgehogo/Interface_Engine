#pragma once
#include "../baseButton.hpp"

namespace ui {
	class Button : public BaseButton {
	protected:
		int interactionIndex;
	
	public:
		Button(IUninteractive *background, int interaction);

		Button(IUninteractive *background, IInteraction *interaction);

		void init(InteractiveInitInfo interactiveInitInfo) override;

		Button* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, Button *&button);
}
