#include "pointingDisplayPanelInteraction.hpp"
#include "../../../general/panel.hpp"

namespace ui {
	PointingDisplayPanelInteraction::PointingDisplayPanelInteraction() : DisplayPanelInteraction() {}
	
	void PointingDisplayPanelInteraction::start(sf::Vector2i) {
		panelManager->displayPanel(panel);
		panel->setParentProcessed(true);
	}
	
	bool PointingDisplayPanelInteraction::update(sf::Vector2i) {
		return false;
	}
	
	void PointingDisplayPanelInteraction::finish(sf::Vector2i) {
		panel->setParentProcessed(false);
	}
	
	PointingDisplayPanelInteraction *PointingDisplayPanelInteraction::copy() {
		PointingDisplayPanelInteraction *pointingDisplayPanelInteraction{new PointingDisplayPanelInteraction{}};
		PanelInteraction::copy(pointingDisplayPanelInteraction);
		return pointingDisplayPanelInteraction;
	}
	
	PointingDisplayPanelInteraction *PointingDisplayPanelInteraction::createFromYaml(const YAML::Node &node) {
		return new PointingDisplayPanelInteraction{};
	}
}

