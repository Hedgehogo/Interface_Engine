#pragma once

#include "event/hidePanelEvent.hpp"
#include "../../click/clickPanelInteraction.hpp"

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
