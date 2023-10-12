#include "PointingDisplayPanelInteraction.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	PointingDisplayPanelInteraction* PointingDisplayPanelInteraction::Make::make(PanelActionInitInfo initInfo) {
		return new PointingDisplayPanelInteraction{std::move(*this), initInfo};
	}
	
	PointingDisplayPanelInteraction::PointingDisplayPanelInteraction(Make&&, PanelActionInitInfo initInfo) :
		BasePanelInteraction(initInfo) {
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
		return new PointingDisplayPanelInteraction{*this};
	}
	
	bool DecodePointer<PointingDisplayPanelInteraction>::decodePointer(const YAML::Node&, PointingDisplayPanelInteraction*& pointingDisplayPanelInteraction) {
		pointingDisplayPanelInteraction = new PointingDisplayPanelInteraction{};
		return true;
	}
}

