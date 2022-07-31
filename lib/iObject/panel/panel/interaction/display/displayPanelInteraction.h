#pragma once
#include "../basePanelInteraction.h"

namespace ui {
	class DisplayPanelInteraction : public virtual BasePanelInteraction {
	public:
		DisplayPanelInteraction* copy() override = 0;
	};
}