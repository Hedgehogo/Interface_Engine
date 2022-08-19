#pragma once
#include "event/hidePanelEvent.hpp"
#include "../../click/clickPanelInteraction.h"

namespace ui {
	class ClickHidePanelInteraction : public ClickPanelInteraction, public HidePanelInteraction {
	public:
		explicit ClickHidePanelInteraction(sf::Mouse::Button button, bool onlyOnParent = false);
		
	protected:
		ClickHidePanelInteraction(HidePanelEvent* hidePanelEvent, sf::Mouse::Button button);
		
	public:
		ClickHidePanelInteraction* copy() override;

        static ClickHidePanelInteraction* createFromYaml(const YAML::Node &node);
	};
}
