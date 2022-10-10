#pragma once
#include "../hidePanelInteraction.hpp"
#include "../../../../../../interaction/iInteraction/empty/emptyInteraction.hpp"

namespace ui {
	class DontHidePanelInteraction : public HidePanelInteraction, public EmptyInteraction {
	public:
		DontHidePanelInteraction() = default;
		
		void init(Panel& panel, IPanelManager &panelManager) override;
		
		void setPanel(Panel& panel) override;
		
		DontHidePanelInteraction* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, DontHidePanelInteraction *&dontHidePanelInteraction);
}
