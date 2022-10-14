#pragma once
#include "event/hidePanelEvent.hpp"
#include "../../click/clickPanelInteraction.hpp"

namespace ui {
	class ClickHidePanelInteraction : public ClickPanelInteraction, public HidePanelInteraction {
	public:
		explicit ClickHidePanelInteraction(KeyHandler::Key button, bool onlyOnParent = false);
		
	protected:
		ClickHidePanelInteraction(HidePanelEvent* hidePanelEvent, KeyHandler::Key button);
		
	public:
		ClickHidePanelInteraction* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, ClickHidePanelInteraction *&clickHidePanelInteraction);
}
