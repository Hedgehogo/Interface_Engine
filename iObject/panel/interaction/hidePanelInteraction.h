#pragma once
#include "panelInteraction.h"

namespace ui {
	class HidePanelInteraction : public PanelInteraction {
	public:
		HidePanelInteraction* copy() override = 0;
	};
}
