#include "clickDisplayPanelInteraction.hpp"
#include "../../../general/panel.hpp"

namespace ui {
	ClickDisplayPanelInteraction::ClickDisplayPanelInteraction(Key key) :
		ClickPanelInteraction(makeBoxPtr<PanelEvent, DisplayPanelEvent>(), key) {
	}
	
	void ClickDisplayPanelInteraction::start(sf::Vector2i) {
		dynamic_cast<PanelEvent&>(*event).getPanel()->setParentProcessed(true);
	}
	
	void ClickDisplayPanelInteraction::finish(sf::Vector2i mousePosition) {
		OneKeyInteraction::finish(mousePosition);
		dynamic_cast<PanelEvent&>(*event).getPanel()->setParentProcessed(false);
	}
	
	ClickDisplayPanelInteraction* ClickDisplayPanelInteraction::copy() {
		return new ClickDisplayPanelInteraction{*this};
	}
	
	bool DecodePointer<ClickDisplayPanelInteraction>::decodePointer(const YAML::Node& node, ClickDisplayPanelInteraction*& clickDisplayPanelInteraction) {
		clickDisplayPanelInteraction = new ClickDisplayPanelInteraction{node["key"].as<Key>()};
		return true;
	}
}