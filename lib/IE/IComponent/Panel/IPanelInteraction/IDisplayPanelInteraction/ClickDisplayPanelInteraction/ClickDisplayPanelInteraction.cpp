#include "ClickDisplayPanelInteraction.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ui {
	ClickDisplayPanelInteraction::ClickDisplayPanelInteraction(Key key) :
		ClickPanelInteraction(makeBoxPtr<PanelEvent, DisplayPanelEvent>(), key) {
	}
	
	void ClickDisplayPanelInteraction::start(sf::Vector2i) {
		dynamic_cast<PanelEvent&>(*event).getPanel()->setParentProcessed(true);
	}
	
	void ClickDisplayPanelInteraction::finish(sf::Vector2i mousePosition) {
		BasicOneKeyInteraction<Panel&>::finish(mousePosition);
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