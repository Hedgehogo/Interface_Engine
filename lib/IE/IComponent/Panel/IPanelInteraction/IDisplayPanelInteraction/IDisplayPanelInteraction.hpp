#pragma once

#include "../IPanelInteraction.hpp"

namespace ie {
	class IDisplayPanelInteraction : public virtual IPanelInteraction {
	public:
		struct Make : public virtual IPanelInteraction::Make {
			IDisplayPanelInteraction* make(PanelActionInitInfo initInfo) override = 0;
		};
		
		IDisplayPanelInteraction* copy() override = 0;
	};
}