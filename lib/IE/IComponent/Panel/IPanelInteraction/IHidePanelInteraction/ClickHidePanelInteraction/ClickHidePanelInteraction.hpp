#pragma once

#include "IE/IComponent/Panel/IPanelInteraction/IHidePanelInteraction/ClickHidePanelInteraction/HidePanelAction/HidePanelAction.hpp"
#include "../../ClickPanelInteraction/ClickPanelInteraction.hpp"

namespace ie {
	class ClickHidePanelInteraction : public ClickPanelInteraction, public IHidePanelInteraction {
	public:
		explicit ClickHidePanelInteraction(Key key, bool onlyOnParent = false);
		
		ClickHidePanelInteraction* copy() override;
	};
	
	template<>
	struct DecodePointer<ClickHidePanelInteraction> {
		static bool decodePointer(const YAML::Node& node, ClickHidePanelInteraction*& clickHidePanelInteraction);
	};
}
