#include "SwitchTabsAction.hpp"
#include "../../../../../../../Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	void SwitchTabsAction::startPressed() {
	}
	
	void SwitchTabsAction::stopPressed() {
		value->setValue(index);
	}
	
	void SwitchTabsAction::whilePressed() {
	}
	
	void SwitchTabsAction::whileNotPressed() {
	}
	
	SwitchTabsAction::SwitchTabsAction(std::shared_ptr<SValue<uint>> value, uint index) : index(index), value(value) {
	}
	
	SwitchTabsAction* SwitchTabsAction::copy() {
		return new SwitchTabsAction{*this};
	}
	
	bool DecodePointer<SwitchTabsAction>::decodePointer(const YAML::Node& node, SwitchTabsAction*& changeObjectAction) {
		changeObjectAction = new SwitchTabsAction{
			Buffer::get<SValue<uint>>(node["value"]),
			convDef(node["index"], 0u)
		};
		return true;
	}
}