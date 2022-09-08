#pragma once
#include "event/hidePanelEvent.hpp"
#include "../../click/clickPanelInteraction.hpp"

namespace ui {
	class ClickHidePanelInteraction : public ClickPanelInteraction, public HidePanelInteraction {
	public:
		explicit ClickHidePanelInteraction(Key button, bool onlyOnParent = false);
		
	protected:
		ClickHidePanelInteraction(HidePanelEvent* hidePanelEvent, Key button);
		
	public:
		ClickHidePanelInteraction* copy() override;

        static ClickHidePanelInteraction* createFromYaml(const YAML::Node &node);
	};
}
