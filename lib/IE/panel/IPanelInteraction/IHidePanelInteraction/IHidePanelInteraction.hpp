#pragma once

#include "../IPanelInteraction.hpp"

namespace ie {
	class IHidePanelInteraction : public virtual IPanelInteraction {
	public:
		struct Make : public virtual IPanelInteraction::Make {
			IHidePanelInteraction* make(PanelActionInitInfo initInfo) override = 0;
		};
		
		Priority getPriority() const override;
		
		IHidePanelInteraction* copy() override = 0;
	};
}
