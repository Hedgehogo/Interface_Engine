#include "clickHidePanelInteraction.hpp"

ui::ClickHidePanelInteraction::ClickHidePanelInteraction(Key button, bool onlyOnParent) :
	ClickPanelInteraction(new HidePanelEvent{onlyOnParent}, button), HidePanelInteraction() {}

ui::ClickHidePanelInteraction::ClickHidePanelInteraction(ui::HidePanelEvent *hidePanelEvent, Key button) :
	ClickPanelInteraction(hidePanelEvent, button), HidePanelInteraction() {}

ui::ClickHidePanelInteraction *ui::ClickHidePanelInteraction::copy() {
	ClickHidePanelInteraction* clickHidePanelInteraction{new ClickHidePanelInteraction(dynamic_cast<HidePanelEvent*>(event->copy()), button)};
	return clickHidePanelInteraction;
}

ui::ClickHidePanelInteraction *ui::ClickHidePanelInteraction::createFromYaml(const YAML::Node &node) {
    Key button;
	bool onlyOnParent{false};
	
    button = createKeyFromYaml(node["button"]);
	if(node["only-on-parent"]) node["only-on-parent"] >> onlyOnParent;
	
    return new ClickHidePanelInteraction{button, onlyOnParent};
}
