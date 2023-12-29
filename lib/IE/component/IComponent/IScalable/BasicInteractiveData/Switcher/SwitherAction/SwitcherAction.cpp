#include "SwitcherAction.hpp"

#include "../Switcher.hpp"

namespace ie {
	SwitcherAction::Make::Make(PSbool value) : value(value) {
	}
	
	SwitcherAction* SwitcherAction::Make::make(ActionInitInfo init_info) {
		return new SwitcherAction{std::move(*this), init_info};
	}
	
	SwitcherAction::SwitcherAction(Make&& make, ActionInitInfo) : value_(std::move(make.value)) {
	}
	
	SwitcherAction::SwitcherAction(PSbool value) : value_(value) {
	}
	
	void SwitcherAction::start_pressed() {
	}
	
	void SwitcherAction::stop_pressed() {
		value_->set_value(!value_->get_value());
	}
	
	void SwitcherAction::while_pressed() {
	}
	
	void SwitcherAction::while_not_pressed() {
	}
	
	SwitcherAction* SwitcherAction::copy() {
		return new SwitcherAction{*this};
	}
	
	bool DecodePointer<SwitcherAction>::decode_pointer(const YAML::Node& node, SwitcherAction*& switcher_action) {
		switcher_action = new SwitcherAction{
			Buffer::get<Sbool>(node["value"])
		};
		return true;
	}
}