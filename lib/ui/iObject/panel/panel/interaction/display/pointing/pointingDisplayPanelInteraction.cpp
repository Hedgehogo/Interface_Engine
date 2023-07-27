#include "pointingDisplayPanelInteraction.hpp"
#include "../../../general/panel.hpp"

namespace ui {
	PointingDisplayPanelInteraction::PointingDisplayPanelInteraction() : DisplayPanelInteraction() {
	}
	
	void PointingDisplayPanelInteraction::start(sf::Vector2i) {
		panelManager->displayPanel(panel);
		panel->setParentProcessed(true);
	}
	
	void PointingDisplayPanelInteraction::update(sf::Vector2i) {
	}
	
	void PointingDisplayPanelInteraction::finish(sf::Vector2i) {
		panel->setParentProcessed(false);
	}
	
	PointingDisplayPanelInteraction* PointingDisplayPanelInteraction::copy() {
		PointingDisplayPanelInteraction* pointingDisplayPanelInteraction{new PointingDisplayPanelInteraction{}};
		PanelInteraction::copy(pointingDisplayPanelInteraction);
		return pointingDisplayPanelInteraction;
	}
	
	bool DecodePointer<PointingDisplayPanelInteraction>::decodePointer(const YAML::Node& node, PointingDisplayPanelInteraction*& pointingDisplayPanelInteraction) {
		{
			pointingDisplayPanelInteraction = new PointingDisplayPanelInteraction{};
			return true;
		}
	}
}

