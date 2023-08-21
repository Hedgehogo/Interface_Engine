#pragma once

#include "../IPanelInteraction.hpp"

namespace ui {
	class IHidePanelInteraction : public virtual IPanelInteraction {
	public:
		IHidePanelInteraction();
		
		Priority getPriority() const override;
		
		IHidePanelInteraction* copy() override = 0;
	};
}
