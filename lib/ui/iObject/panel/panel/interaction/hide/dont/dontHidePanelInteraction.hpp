#pragma once
#include "../hidePanelInteraction.hpp"
#include "../../../../../../interaction/iInteraction/empty/emptyInteraction.h"

namespace ui {
	class DontHidePanelInteraction : public HidePanelInteraction, public EmptyInteraction {
	public:
		DontHidePanelInteraction() = default;
		
		void init(Panel& panel, PanelManager& panelManager) override;
		
		void setPanel(Panel& panel) override;
		
		DontHidePanelInteraction* copy() override;
		
		static DontHidePanelInteraction* createFromYaml(const YAML::Node &node);
	};
}
