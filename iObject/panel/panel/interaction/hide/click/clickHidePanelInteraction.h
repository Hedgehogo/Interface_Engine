#pragma once
#include "event/hidePanelEvent.h"
#include "../../click/clickPanelInteraction.h"

namespace ui {
	class ClickHidePanelInteraction : public ClickPanelInteraction, public HidePanelInteraction {
	public:
		explicit ClickHidePanelInteraction(sf::Mouse::Button button);
		
	protected:
		ClickHidePanelInteraction(HidePanelEvent* hidePanelEvent, sf::Mouse::Button button);
		
	public:
		ClickHidePanelInteraction* copy() override;
	};
}
