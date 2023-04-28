#pragma once
#include "event/hidePanelEvent.hpp"
#include "../../click/clickPanelInteraction.hpp"

namespace ui {
	class ClickHidePanelInteraction : public ClickPanelInteraction, public HidePanelInteraction {
	public:
		explicit ClickHidePanelInteraction(Key key, bool onlyOnParent = false);
		
	protected:
		ClickHidePanelInteraction(HidePanelEvent* hidePanelEvent, Key key);
		
	public:
		ClickHidePanelInteraction* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, ClickHidePanelInteraction *&clickHidePanelInteraction);
	
	template<>
	struct DecodePointer<ClickHidePanelInteraction> {
		static bool decodePointer(const YAML::Node &node, ClickHidePanelInteraction *&clickHidePanelInteraction);
	};
}
