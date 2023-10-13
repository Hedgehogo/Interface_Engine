#include "SwitchTabsAction.hpp"
#include "IE/modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	SwitchTabsAction::Make::Make(uint index) : index(index) {
	}
	
	SwitchTabsAction* SwitchTabsAction::Make::make(BasicActionInitInfo<BoxSwitchTabs&> initInfo) {
		return new SwitchTabsAction{std::move(*this), initInfo};
	}
	
	SwitchTabsAction::SwitchTabsAction(Make&& make, BasicActionInitInfo<BoxSwitchTabs&> initInfo) :
		BaseSwitchTabsAction(initInfo), index(make.index), value(box->getValue()) {
	}
	
	SwitchTabsAction::SwitchTabsAction(uint index) : index(index), value(nullptr) {
	}
	
	void SwitchTabsAction::init(BasicActionInitInfo<BoxSwitchTabs&> initInfo) {
		BaseSwitchTabsAction::init(initInfo);
		value = box->getValue();
	}
	
	void SwitchTabsAction::startPressed() {
	}
	
	void SwitchTabsAction::stopPressed() {
		value->setValue(index);
	}
	
	void SwitchTabsAction::whilePressed() {
	}
	
	void SwitchTabsAction::whileNotPressed() {
	}
	
	SwitchTabsAction* SwitchTabsAction::copy() {
		return new SwitchTabsAction{*this};
	}
	
	bool DecodePointer<SwitchTabsAction>::decodePointer(const YAML::Node& node, SwitchTabsAction*& changeObjectAction) {
		changeObjectAction = new SwitchTabsAction{convDef(node["index"], 0u)};
		return true;
	}
}