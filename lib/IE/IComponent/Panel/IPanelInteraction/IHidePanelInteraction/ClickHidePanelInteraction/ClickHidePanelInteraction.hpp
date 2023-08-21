#pragma once

#include "HidePanelEvent/HidePanelEvent.hpp"
#include "../../ClickPanelInteraction/ClickPanelInteraction.hpp"

namespace ui {
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
