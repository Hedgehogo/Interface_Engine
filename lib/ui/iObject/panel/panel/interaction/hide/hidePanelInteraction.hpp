#pragma once
#include "../basePanelInteraction.hpp"

namespace ui {
	class HidePanelInteraction : public virtual BasePanelInteraction {
	public:
		HidePanelInteraction();
		
		Priority getPriority() const override;
		
		HidePanelInteraction* copy() override = 0;
	};
}
