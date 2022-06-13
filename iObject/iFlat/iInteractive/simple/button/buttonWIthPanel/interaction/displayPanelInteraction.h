#pragma once
#include "../../../../../../panel/interaction/panelInteraction.h"

namespace ui {
	class DisplayPanelInteraction : public PanelInteraction {
	public:
		DisplayPanelInteraction* copy() override = 0;
	};
}