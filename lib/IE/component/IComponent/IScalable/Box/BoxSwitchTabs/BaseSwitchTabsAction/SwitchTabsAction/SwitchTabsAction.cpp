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
	
	void SwitchTabsAction::init(BasicActionInitInfo<BoxSwitchTabs&> init_info) {
		BaseSwitchTabsAction::init(init_info);
		value_ = box_->get_value();
	}
	
	void SwitchTabsAction::start_pressed() {
	}
	
	void SwitchTabsAction::stop_pressed() {
		value_.set(index_);
	}
	
	void SwitchTabsAction::while_pressed() {
	}
	
	void SwitchTabsAction::while_not_pressed() {
	}
	
	SwitchTabsAction* SwitchTabsAction::copy() {
		return new SwitchTabsAction{*this};
	}
}

orl::Option<ie::SwitchTabsAction::Make> ieml::Decode<char, ie::SwitchTabsAction::Make>::decode(ieml::Node const& node) {
	return {{node.get_as<size_t>("index").ok_or(0u)}};
}