#pragma once
#include "../../../../interaction/iInteraction/iInteraction.h"

namespace ui {
	class Panel;
	class PanelManager;
	class BasePanelInteraction : public virtual IInteraction {
	public:
		BasePanelInteraction() = default;
		
		virtual void init(Panel& panel, PanelManager& panelManager) = 0;
		
		virtual void setPanel(Panel& panel) = 0;
		
		BasePanelInteraction* copy() override = 0;
	};
}
