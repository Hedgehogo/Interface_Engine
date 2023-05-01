#include "switcherEvent.hpp"

#include "../switcher.hpp"

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
		return new SwitcherEvent(value);
	}
	
}