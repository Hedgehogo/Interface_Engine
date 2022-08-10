#include "clickHidePanelInteraction.h"

ui::ClickHidePanelInteraction::ClickHidePanelInteraction(sf::Mouse::Button button) :
	ClickPanelInteraction(new HidePanelEvent{}, button), HidePanelInteraction() {}

ui::ClickHidePanelInteraction::ClickHidePanelInteraction(ui::HidePanelEvent *hidePanelEvent, sf::Mouse::Button button) :
	ClickPanelInteraction(hidePanelEvent, button), HidePanelInteraction() {}

ui::ClickHidePanelInteraction *ui::ClickHidePanelInteraction::copy() {
	ClickHidePanelInteraction* clickHidePanelInteraction{new ClickHidePanelInteraction(dynamic_cast<HidePanelEvent*>(event->copy()), button)};
	return clickHidePanelInteraction;
}

ui::ClickHidePanelInteraction *ui::ClickHidePanelInteraction::createFromYaml(const YAML::Node &node) {
    sf::Mouse::Button button;
    node["button"] >> button;
    return new ClickHidePanelInteraction{button};
}
