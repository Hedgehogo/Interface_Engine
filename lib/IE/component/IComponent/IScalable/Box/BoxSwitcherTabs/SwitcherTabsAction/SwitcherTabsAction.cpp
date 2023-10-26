#include "SwitcherTabsAction.hpp"
#include "../BoxSwitcherTabs.hpp"

namespace ie {
	SwitcherTabsAction::Make::Make(PISint value) : value(std::move(value)) {
	}
	
	SwitcherTabsAction* SwitcherTabsAction::Make::make(BasicActionInitInfo<BoxSwitcherTabs&> init_info) {
		return new SwitcherTabsAction{std::move(*this), init_info};
	}
	
	SwitcherTabsAction::SwitcherTabsAction(Make&& make, BasicActionInitInfo<BoxSwitcherTabs&> init_info) :
		value_(std::move(make.value)), switcher_tabs_(&init_info.additional) {
	}
	
	SwitcherTabsAction::SwitcherTabsAction(PISint value) :
		value_(std::move(value)), switcher_tabs_(nullptr) {
	}
	
	void SwitcherTabsAction::init(BasicActionInitInfo<BoxSwitcherTabs&> init_info) {
		switcher_tabs_ = &init_info.additional;
	}
	
	void SwitcherTabsAction::start_pressed() {}
	
	void SwitcherTabsAction::stop_pressed() {
		value_->set_value(switcher_tabs_->get_tab(sf::Vector2f(mouse_position)));
	}
	
	void SwitcherTabsAction::while_pressed() {}
	
	void SwitcherTabsAction::while_not_pressed() {}
	
	SwitcherTabsAction* SwitcherTabsAction::copy() {
		return new SwitcherTabsAction{*this};
	}
}