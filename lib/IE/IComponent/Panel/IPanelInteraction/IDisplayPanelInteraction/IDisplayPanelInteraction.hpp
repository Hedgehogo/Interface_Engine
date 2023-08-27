#pragma once

#include "../IPanelInteraction.hpp"

namespace ie {
	class IDisplayPanelInteraction : public virtual IPanelInteraction {
	public:
		IDisplayPanelInteraction* copy() override = 0;
	};
}