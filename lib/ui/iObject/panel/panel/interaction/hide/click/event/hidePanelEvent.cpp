#include "hidePanelEvent.hpp"
#include "../../../../general/panel.hpp"

ui::HidePanelEvent::HidePanelEvent(bool onlyOnParent) : onlyOnParent(onlyOnParent) {}

void ui::HidePanelEvent::startPressed() {}

void ui::HidePanelEvent::whilePressed() {}

void ui::HidePanelEvent::stopPressed() {
	sf::Vector2f pointPosition {static_cast<sf::Vector2f>(mousePosition)};
	if(onlyOnParent ? panel->getParentProcessed() : !panel->inPanel(pointPosition) && !panel->inConstPanels(pointPosition) && panel->isFree())
		panelManager->hidePanel(panel);
}

void ui::HidePanelEvent::whileNotPressed() {}

ui::HidePanelEvent *ui::HidePanelEvent::copy() {
	HidePanelEvent* hidePanelEvent{new HidePanelEvent()};
	hidePanelEvent->init(*panel, *panelManager);
	return hidePanelEvent;
}

ui::HidePanelEvent *ui::HidePanelEvent::createFromYaml(const YAML::Node &node) {
	bool onlyOnParent{false};
	
	if(node["only-on-parent"]) node["only-on-parent"] >> onlyOnParent;
	
    return new HidePanelEvent{onlyOnParent};
}
