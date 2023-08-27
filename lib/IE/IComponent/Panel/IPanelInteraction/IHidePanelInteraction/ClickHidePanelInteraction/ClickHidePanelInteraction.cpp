#include "ClickHidePanelInteraction.hpp"

namespace ie {
	ClickHidePanelInteraction::Make::Make(Key key, bool onlyOnParent) :
		key(key), onlyOnParent(onlyOnParent) {
	}
	
	ClickHidePanelInteraction* ClickHidePanelInteraction::Make::make(PanelActionInitInfo initInfo) {
		return new ClickHidePanelInteraction{std::move(*this), initInfo};
	}
	
	ClickHidePanelInteraction::ClickHidePanelInteraction(Make&& make, PanelActionInitInfo initInfo) :
		ClickPanelInteraction(makeBoxPtr<HidePanelAction>(make.onlyOnParent), make.key, initInfo) {
	}
	
	ClickHidePanelInteraction::ClickHidePanelInteraction(Key key, bool onlyOnParent) :
		ClickPanelInteraction(makeBoxPtr<HidePanelAction>(onlyOnParent), key) {
	}
	
	ClickHidePanelInteraction* ClickHidePanelInteraction::copy() {
		return new ClickHidePanelInteraction{*this};
	}
	
	bool DecodePointer<ClickHidePanelInteraction>::decodePointer(const YAML::Node& node, ClickHidePanelInteraction*& clickHidePanelInteraction) {
		clickHidePanelInteraction = new ClickHidePanelInteraction{
			node["key"].as<Key>(),
			convDef(node["only-on-parent"], false)
		};
		return true;
	}
}
