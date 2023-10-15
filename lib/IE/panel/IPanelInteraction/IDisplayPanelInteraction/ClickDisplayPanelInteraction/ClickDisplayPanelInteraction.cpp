#include "ClickDisplayPanelInteraction.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	ClickDisplayPanelInteraction::Make::Make(Key key) : key(key) {
	}
	
	ClickDisplayPanelInteraction* ClickDisplayPanelInteraction::Make::make(PanelActionInitInfo initInfo) {
		return new ClickDisplayPanelInteraction{std::move(*this), initInfo};
	}
	
	ClickDisplayPanelInteraction::ClickDisplayPanelInteraction(Make&& make, PanelActionInitInfo initInfo) :
		ClickPanelInteraction(make_box_ptr<DisplayPanelAction::Make>(), make.key, initInfo) {
	}
	
	ClickDisplayPanelInteraction::ClickDisplayPanelInteraction(Key key) :
		ClickPanelInteraction(make_box_ptr<DisplayPanelAction>(), key) {
	}
	
	void ClickDisplayPanelInteraction::start(sf::Vector2i) {
		dynamic_cast<PanelAction&>(*action).getPanel()->setParentProcessed(true);
	}
	
	void ClickDisplayPanelInteraction::finish(sf::Vector2i mousePosition) {
		BasicOneKeyInteraction<Panel&>::finish(mousePosition);
		dynamic_cast<PanelAction&>(*action).getPanel()->setParentProcessed(false);
	}
	
	ClickDisplayPanelInteraction* ClickDisplayPanelInteraction::copy() {
		return new ClickDisplayPanelInteraction{*this};
	}
	
	bool DecodePointer<ClickDisplayPanelInteraction>::decodePointer(const YAML::Node& node, ClickDisplayPanelInteraction*& clickDisplayPanelInteraction) {
		clickDisplayPanelInteraction = new ClickDisplayPanelInteraction{node["key"].as<Key>()};
		return true;
	}
}