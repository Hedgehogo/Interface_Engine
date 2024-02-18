#include "SwitcherAction.hpp"

#include "../Switcher.hpp"

namespace ie {
	SwitcherAction::Make::Make(MakeDyn<ISMBool> value) : value(std::move(value)) {
	}
	
	SwitcherAction* SwitcherAction::Make::make(ActionInitInfo init_info) {
		return new SwitcherAction{std::move(*this), init_info};
	}
	
	SwitcherAction::SwitcherAction(Make&& make, ActionInitInfo init_info) : value_(make.value.make({init_info.dyn_buffer, init_info.update_manager})) {
	}
	
	SwitcherAction::SwitcherAction(ISMBool& value) : value_(value) {
	}
	
	void SwitcherAction::start_pressed() {
	}
	
	void SwitcherAction::stop_pressed() {
		value_.set(!value_.get());
	}
	
	void SwitcherAction::while_pressed() {
	}
	
	void SwitcherAction::while_not_pressed() {
	}
}

orl::Option<ie::SwitcherAction::Make> ieml::Decode<char, ie::SwitcherAction::Make>::decode(ieml::Node const& node) {
	return ie::SwitcherAction::Make{
		node.at("value").except().as<ie::MakeDyn<ie::ISMBool> >().except()
	};
}
