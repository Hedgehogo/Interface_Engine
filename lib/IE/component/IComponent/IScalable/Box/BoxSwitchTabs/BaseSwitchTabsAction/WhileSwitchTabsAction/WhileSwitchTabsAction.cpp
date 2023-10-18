#include "WhileSwitchTabsAction.hpp"

namespace ie {
	WhileSwitchTabsAction::Make::Make(int step) : step(step) {
	}
	
	WhileSwitchTabsAction* WhileSwitchTabsAction::Make::make(BasicActionInitInfo<BoxSwitchTabs&> init_info) {
		return new WhileSwitchTabsAction{std::move(*this), init_info};
	}
	
	WhileSwitchTabsAction::WhileSwitchTabsAction(Make&& make, BasicActionInitInfo<BoxSwitchTabs&> init_info) :
		BaseSwitchTabsAction(init_info), size(box->get_array_size()), value(box->get_value()), step(make.step) {
	}
	
	WhileSwitchTabsAction::WhileSwitchTabsAction(int step) :
		size(0), value(nullptr), step(step) {
	}
	
	void WhileSwitchTabsAction::init(BasicActionInitInfo<BoxSwitchTabs&> init_info) {
		BaseSwitchTabsAction::init(init_info);
		size = box->get_array_size();
		value = box->get_value();
	}
	
	void WhileSwitchTabsAction::start_pressed() {
	}
	
	void WhileSwitchTabsAction::stop_pressed() {
		int index_value = value->get_value();
		index_value += step;
		index_value = (((index_value % size) + size) % size);
		value->set_value(index_value);
	}
	
	void WhileSwitchTabsAction::while_pressed() {
	}
	
	void WhileSwitchTabsAction::while_not_pressed() {
	}
	
	WhileSwitchTabsAction* WhileSwitchTabsAction::copy() {
		return new WhileSwitchTabsAction{*this};
	}
	
	bool DecodePointer<WhileSwitchTabsAction>::decode_pointer(const YAML::Node&, WhileSwitchTabsAction*& while_changing_objects_action) {
		while_changing_objects_action = new WhileSwitchTabsAction{};
		return true;
	}
}