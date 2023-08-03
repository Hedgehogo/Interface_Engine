#include "../boxSwitcherTabs.hpp"

namespace ui {
	SwitcherTabsEvent::SwitcherTabsEvent(const PISint& value, BoxSwitcherTabs* switcherTabs) : value(value), switcherTabs(switcherTabs) {}
	
	void SwitcherTabsEvent::startPressed() {}
	
	void SwitcherTabsEvent::stopPressed() {
		value->setValue(switcherTabs->getTab(sf::Vector2f(mousePosition)));
	}
	
	void SwitcherTabsEvent::whilePressed() {}
	
	void SwitcherTabsEvent::whileNotPressed() {}
	
	SwitcherTabsEvent* SwitcherTabsEvent::copy() {
		return new SwitcherTabsEvent{*this};
	}
}