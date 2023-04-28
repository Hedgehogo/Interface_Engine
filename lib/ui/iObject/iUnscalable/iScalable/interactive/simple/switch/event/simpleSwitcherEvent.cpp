#include "simpleSwitcherEvent.hpp"

#include "../simpleSwither.hpp"

namespace ui {
	SimpleSwitcherEvent::SimpleSwitcherEvent(SimpleSwitcher& switcher) : switcher(&switcher) {
	}
	
	void SimpleSwitcherEvent::startPressed() {
	}
	
	void SimpleSwitcherEvent::stopPressed() {
		switcher->switchValue();
	}
	
	void SimpleSwitcherEvent::whilePressed() {
	}
	
	void SimpleSwitcherEvent::whileNotPressed() {
	}
	
	void SimpleSwitcherEvent::setSwitcher(SimpleSwitcher& switcher) {
		this->switcher = &switcher;
	}
	
	SimpleSwitcherEvent* SimpleSwitcherEvent::copy() {
		return new SimpleSwitcherEvent(*switcher);
	}
	
}