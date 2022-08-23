#include "clickHidePanelInteraction.hpp"

ui::ClickHidePanelInteraction::ClickHidePanelInteraction(sf::Mouse::Button button, bool onlyOnParent) :
	ClickPanelInteraction(new HidePanelEvent{onlyOnParent}, button), HidePanelInteraction() {}

ui::ClickHidePanelInteraction::ClickHidePanelInteraction(ui::HidePanelEvent *hidePanelEvent, sf::Mouse::Button button) :
	ClickPanelInteraction(hidePanelEvent, button), HidePanelInteraction() {}

ui::ClickHidePanelInteraction *ui::ClickHidePanelInteraction::copy() {
	ClickHidePanelInteraction* clickHidePanelInteraction{new ClickHidePanelInteraction(dynamic_cast<HidePanelEvent*>(event->copy()), button)};
	return clickHidePanelInteraction;
}

ui::ClickHidePanelInteraction *ui::ClickHidePanelInteraction::createFromYaml(const YAML::Node &node) {
    sf::Mouse::Button button;
	bool onlyOnParent{false};
	
    node["button"] >> button;
	if(node["only-on-parent"]) node["only-on-parent"] >> onlyOnParent;
	
    return new ClickHidePanelInteraction{button, onlyOnParent};
}
