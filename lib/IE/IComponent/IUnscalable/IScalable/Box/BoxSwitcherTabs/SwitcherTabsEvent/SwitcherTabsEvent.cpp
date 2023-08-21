#include "SwitcherTabsEvent.hpp"
#include "../BoxSwitcherTabs.hpp"

namespace ui {
	SwitcherTabsEvent::SwitcherTabsEvent(PISint value, BoxSwitcherTabs& switcherTabs) :
		value(std::move(value)), switcherTabs(&switcherTabs) {}
	
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