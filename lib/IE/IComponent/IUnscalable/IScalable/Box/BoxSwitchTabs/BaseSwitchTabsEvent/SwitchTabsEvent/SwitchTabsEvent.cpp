#include "SwitchTabsEvent.hpp"
#include "../../../../../../../Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	void SwitchTabsEvent::startPressed() {
	}
	
	void SwitchTabsEvent::stopPressed() {
		value->setValue(index);
	}
	
	void SwitchTabsEvent::whilePressed() {
	}
	
	void SwitchTabsEvent::whileNotPressed() {
	}
	
	SwitchTabsEvent::SwitchTabsEvent(std::shared_ptr<SValue<uint>> value, uint index) : index(index), value(value) {
	}
	
	SwitchTabsEvent* SwitchTabsEvent::copy() {
		return new SwitchTabsEvent{*this};
	}
	
	bool DecodePointer<SwitchTabsEvent>::decodePointer(const YAML::Node& node, SwitchTabsEvent*& changeObjectEvent) {
		changeObjectEvent = new SwitchTabsEvent{
			Buffer::get<SValue<uint>>(node["value"]),
			convDef(node["index"], 0u)
		};
		return true;
	}
}