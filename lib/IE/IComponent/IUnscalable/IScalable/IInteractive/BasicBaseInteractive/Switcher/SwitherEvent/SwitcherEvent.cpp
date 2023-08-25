#include "SwitcherEvent.hpp"

#include "../Switcher.hpp"

namespace ui {
	SwitcherEvent::SwitcherEvent(PSbool value) : value(value) {
	}
	
	void SwitcherEvent::startPressed() {
	}
	
	void SwitcherEvent::stopPressed() {
		value->setValue(!value->getValue());
	}
	
	void SwitcherEvent::whilePressed() {
	}
	
	void SwitcherEvent::whileNotPressed() {
	}
	
	SwitcherEvent* SwitcherEvent::copy() {
		return new SwitcherEvent{*this};
	}
	
	bool DecodePointer<SwitcherEvent>::decodePointer(const YAML::Node& node, SwitcherEvent*& switcherEvent) {
		switcherEvent = new SwitcherEvent{
			Buffer::get<Sbool>(node["value"])
		};
		return true;
	}
}