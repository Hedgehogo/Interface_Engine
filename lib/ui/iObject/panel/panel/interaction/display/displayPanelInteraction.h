#pragma once
#include "../basePanelInteraction.hpp"

namespace ui {
	class DisplayPanelInteraction : public virtual BasePanelInteraction {
	public:
		DisplayPanelInteraction* copy() override = 0;
	};
}