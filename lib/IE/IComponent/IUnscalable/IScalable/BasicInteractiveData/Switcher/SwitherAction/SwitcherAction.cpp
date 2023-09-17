#include "SwitcherAction.hpp"

#include "../Switcher.hpp"

namespace ie {
	SwitcherAction::Make::Make(PSbool value) : value(value) {
	}
	
	SwitcherAction* SwitcherAction::Make::make(ActionInitInfo initInfo) {
		return new SwitcherAction{std::move(*this), initInfo};
	}
	
	SwitcherAction::SwitcherAction(Make&& make, ActionInitInfo) : value(std::move(make.value)) {
	}
	
	SwitcherAction::SwitcherAction(PSbool value) : value(value) {
	}
	
	void SwitcherAction::startPressed() {
	}
	
	void SwitcherAction::stopPressed() {
		value->setValue(!value->getValue());
	}
	
	void SwitcherAction::whilePressed() {
	}
	
	void SwitcherAction::whileNotPressed() {
	}
	
	SwitcherAction* SwitcherAction::copy() {
		return new SwitcherAction{*this};
	}
	
	bool DecodePointer<SwitcherAction>::decodePointer(const YAML::Node& node, SwitcherAction*& switcherAction) {
		switcherAction = new SwitcherAction{
			Buffer::get<Sbool>(node["value"])
		};
		return true;
	}
}