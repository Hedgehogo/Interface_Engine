#include "SwitchTabsAction.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"

namespace ie {
	SwitchTabsAction::Make::Make(uint index) : index(index) {
	}
	
	SwitchTabsAction* SwitchTabsAction::Make::make(BasicActionInitInfo<BoxSwitchTabs&> init_info) {
		return new SwitchTabsAction{std::move(*this), init_info};
	}
	
	SwitchTabsAction::SwitchTabsAction(Make&& make, BasicActionInitInfo<BoxSwitchTabs&> init_info) :
		BaseSwitchTabsAction(init_info), index(make.index), value(box->get_value()) {
	}
	
	SwitchTabsAction::SwitchTabsAction(uint index) : index(index), value(nullptr) {
	}
	
	void SwitchTabsAction::init(BasicActionInitInfo<BoxSwitchTabs&> init_info) {
		BaseSwitchTabsAction::init(init_info);
		value = box->get_value();
	}
	
	void SwitchTabsAction::start_pressed() {
	}
	
	void SwitchTabsAction::stop_pressed() {
		value->set_value(index);
	}
	
	void SwitchTabsAction::while_pressed() {
	}
	
	void SwitchTabsAction::while_not_pressed() {
	}
	
	SwitchTabsAction* SwitchTabsAction::copy() {
		return new SwitchTabsAction{*this};
	}
	
	bool DecodePointer<SwitchTabsAction>::decode_pointer(const YAML::Node& node, SwitchTabsAction*& change_object_action) {
		change_object_action = new SwitchTabsAction{conv_def(node["index"], 0u)};
		return true;
	}
}