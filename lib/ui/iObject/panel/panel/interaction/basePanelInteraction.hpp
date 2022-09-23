#pragma once
#include "../../../../interaction/iInteraction/iInteraction.hpp"

namespace ui {
	class Panel;
	class IPanelManager;
	class BasePanelInteraction : public virtual IInteraction {
	public:
		BasePanelInteraction() = default;
		
		virtual void init(Panel& panel, IPanelManager &panelManager) = 0;
		
		virtual void setPanel(Panel& panel) = 0;
		
		BasePanelInteraction* copy() override = 0;
	};
}
