#include "SwitcherAction.hpp"

#include "../Switcher.hpp"

namespace ie {
	SwitcherAction::Make::Make(MakeDyn<ISMBool> value) : value(std::move(value)) {
	}
	
	auto SwitcherAction::Make::make(ActionInitInfo init_info) -> SwitcherAction* {
		return new SwitcherAction{std::move(*this), init_info};
	}
	
	SwitcherAction::SwitcherAction(Make&& make, ActionInitInfo init_info) :
		value_(make.value.make({init_info.dyn_buffer, init_info.update_manager})) {
	}
	
	SwitcherAction::SwitcherAction(ISMBool& value) : value_(value) {
	}
	
	auto SwitcherAction::start_pressed() -> void {
	}
	
	auto SwitcherAction::stop_pressed() -> void {
		value_.set(!value_.get());
	}
	
	auto SwitcherAction::while_pressed() -> void {
	}
	
	auto SwitcherAction::while_not_pressed() -> void {
	}
}

auto ieml::Decode<char, ie::SwitcherAction::Make>::decode(ieml::Node const& node) -> orl::Option<ie::SwitcherAction::Make> {
	return {{node.at("value").except().as<ie::MakeDyn<ie::ISMBool> >().except()}};
}
