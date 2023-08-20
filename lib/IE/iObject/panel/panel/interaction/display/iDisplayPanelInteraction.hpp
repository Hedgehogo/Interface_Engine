#pragma once

#include "../iPanelInteraction.hpp"

namespace ui {
	class IDisplayPanelInteraction : public virtual IPanelInteraction {
	public:
		IDisplayPanelInteraction* copy() override = 0;
	};
}