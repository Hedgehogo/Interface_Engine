#include "SwitchTabsAction.hpp"
#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	SwitchTabsAction::Make::Make(size_t index) : index(index) {
	}
	
	SwitchTabsAction* SwitchTabsAction::Make::make(BasicActionInitInfo<BoxSwitchTabs&> init_info) {
		return new SwitchTabsAction{std::move(*this), init_info};
	}
	
	SwitchTabsAction::SwitchTabsAction(Make&& make, BasicActionInitInfo<BoxSwitchTabs&> init_info) :
		BaseSwitchTabsAction(init_info), index_(make.index), value_(box_->get_value()) {
	}
	
	SwitchTabsAction::SwitchTabsAction(size_t index) : index_(index), value_(nullptr) {
	}
	
	void SwitchTabsAction::init(BasicActionInitInfo<BoxSwitchTabs&> init_info) {
		BaseSwitchTabsAction::init(init_info);
		value_ = box_->get_value();
	}
	
	void SwitchTabsAction::start_pressed() {
	}
	
	void SwitchTabsAction::stop_pressed() {
		value_->set_value(index_);
	}
	
	void SwitchTabsAction::while_pressed() {
	}
	
	void SwitchTabsAction::while_not_pressed() {
	}
	
	SwitchTabsAction* SwitchTabsAction::copy() {
		return new SwitchTabsAction{*this};
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<SwitchTabsAction>::decode_pointer(const YAML::Node& node, SwitchTabsAction*& change_object_action) {
		change_object_action = new SwitchTabsAction{conv_def(node["index"], 0u)};
		return true;

	}
	*/
}