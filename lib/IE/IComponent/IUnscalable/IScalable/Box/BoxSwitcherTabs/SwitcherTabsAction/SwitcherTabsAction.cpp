#include "SwitcherTabsAction.hpp"
#include "../BoxSwitcherTabs.hpp"

namespace ie {
	SwitcherTabsAction::SwitcherTabsAction(PISint value) :
		value(std::move(value)), switcherTabs(nullptr) {}
	
	void SwitcherTabsAction::init(BasicActionInitInfo<BoxSwitcherTabs&> initInfo) {
		switcherTabs = &initInfo.additional;
	}
	
	void SwitcherTabsAction::startPressed() {}
	
	void SwitcherTabsAction::stopPressed() {
		value->setValue(switcherTabs->getTab(sf::Vector2f(mousePosition)));
	}
	
	void SwitcherTabsAction::whilePressed() {}
	
	void SwitcherTabsAction::whileNotPressed() {}
	
	SwitcherTabsAction* SwitcherTabsAction::copy() {
		return new SwitcherTabsAction{*this};
	}
}