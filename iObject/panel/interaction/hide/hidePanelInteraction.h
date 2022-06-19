#pragma once
#include "../basePanelInteraction.h"

namespace ui {
	class HidePanelInteraction : public virtual BasePanelInteraction {
	public:
		HidePanelInteraction();
		
		HidePanelInteraction* copy() override = 0;
	};
}
