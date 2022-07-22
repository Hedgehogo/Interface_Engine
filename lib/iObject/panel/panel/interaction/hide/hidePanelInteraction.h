#pragma once
#include "../basePanelInteraction.h"

namespace ui {
	class HidePanelInteraction : public virtual BasePanelInteraction {
	public:
		HidePanelInteraction();
		
		InteractionType getType() const override;
		
		HidePanelInteraction* copy() override = 0;
	};
}
