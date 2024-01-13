#include "SwitcherAction.hpp"

#include "../Switcher.hpp"

namespace ie {
	SwitcherAction::Make::Make(MakeDyn<ISBool> value) : value(std::move(value)) {
	}
	
	SwitcherAction* SwitcherAction::Make::make(ActionInitInfo init_info) {
		return new SwitcherAction{std::move(*this), init_info};
	}
	
	SwitcherAction::SwitcherAction(Make&& make, ActionInitInfo init_info) : value_(make.value.make(init_info.dyn_buffer)) {
	}
	
	SwitcherAction::SwitcherAction(ISBool& value) : value_(value) {
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
	
	SwitcherAction* SwitcherAction::copy() {
		return new SwitcherAction{*this};
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<SwitcherAction>::decode_pointer(const YAML::Node& node, SwitcherAction*& switcher_action) {
		switcher_action = new SwitcherAction{
			Buffer::get<Sbool>(node["value"])
		};
		return true;

	}
	*/
}