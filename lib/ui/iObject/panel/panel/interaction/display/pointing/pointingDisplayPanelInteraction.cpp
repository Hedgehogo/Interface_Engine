#include "pointingDisplayPanelInteraction.hpp"
#include "../../../general/panel.hpp"

ui::PointingDisplayPanelInteraction::PointingDisplayPanelInteraction() : DisplayPanelInteraction() {}

void ui::PointingDisplayPanelInteraction::start(sf::Vector2i) {
	panelManager->displayPanel(panel);
	panel->setParentProcessed(true);
}

bool ui::PointingDisplayPanelInteraction::update(sf::Vector2i) { return false; }

void ui::PointingDisplayPanelInteraction::finish(sf::Vector2i) {
	panel->setParentProcessed(false);
}

ui::PointingDisplayPanelInteraction *ui::PointingDisplayPanelInteraction::copy() {
	PointingDisplayPanelInteraction* pointingDisplayPanelInteraction {new PointingDisplayPanelInteraction{}};
	PanelInteraction::copy(pointingDisplayPanelInteraction);
	return pointingDisplayPanelInteraction;
}

ui::PointingDisplayPanelInteraction *ui::PointingDisplayPanelInteraction::createFromYaml(const YAML::Node &node) {
    return new PointingDisplayPanelInteraction{};
}

