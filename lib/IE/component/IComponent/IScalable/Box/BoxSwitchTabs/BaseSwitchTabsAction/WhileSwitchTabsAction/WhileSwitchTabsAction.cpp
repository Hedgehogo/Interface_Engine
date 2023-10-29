#include "WhileSwitchTabsAction.hpp"

namespace ie {
	WhileSwitchTabsAction::Make::Make(int step) : step(step) {
	}
	
	WhileSwitchTabsAction* WhileSwitchTabsAction::Make::make(BasicActionInitInfo<BoxSwitchTabs&> init_info) {
		return new WhileSwitchTabsAction{std::move(*this), init_info};
	}
	
	WhileSwitchTabsAction::WhileSwitchTabsAction(Make&& make, BasicActionInitInfo<BoxSwitchTabs&> init_info) :
		BaseSwitchTabsAction(init_info), size_(box_->get_array_size()), value_(box_->get_value()), step_(make.step) {
	}
	
	WhileSwitchTabsAction::WhileSwitchTabsAction(int step) :
		size_(0), value_(nullptr), step_(step) {
	}
	
	void WhileSwitchTabsAction::init(BasicActionInitInfo<BoxSwitchTabs&> init_info) {
		BaseSwitchTabsAction::init(init_info);
		size_ = box_->get_array_size();
		value_ = box_->get_value();
	}
	
	void WhileSwitchTabsAction::start_pressed() {
	}
	
	void WhileSwitchTabsAction::stop_pressed() {
		int index_value = value_->get_value();
		index_value += step_;
		index_value = (((index_value % size_) + size_) % size_);
		value_->set_value(index_value);
	}
	
	void WhileSwitchTabsAction::while_pressed() {
	}
	
	void WhileSwitchTabsAction::while_not_pressed() {
	}
	
	WhileSwitchTabsAction* WhileSwitchTabsAction::copy() {
		return new WhileSwitchTabsAction{*this};
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<WhileSwitchTabsAction>::decode_pointer(const YAML::Node&, WhileSwitchTabsAction*& while_changing_objects_action) {
		while_changing_objects_action = new WhileSwitchTabsAction{};
		return true;
	}
	*/
}