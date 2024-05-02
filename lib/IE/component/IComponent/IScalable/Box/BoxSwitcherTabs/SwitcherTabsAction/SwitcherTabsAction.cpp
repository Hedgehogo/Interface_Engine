#include "SwitcherTabsAction.hpp"
#include "../BoxSwitcherTabs.hpp"

namespace ie {
	SwitcherTabsAction::Make::Make(MakeDyn<ISMRSize> value) : value(std::move(value)) {
	}
	
	auto SwitcherTabsAction::Make::make(BasicActionInitInfo<BoxSwitcherTabs&> init_info) -> SwitcherTabsAction* {
		return new SwitcherTabsAction{std::move(*this), init_info};
	}
	
	SwitcherTabsAction::SwitcherTabsAction(Make&& make, BasicActionInitInfo<BoxSwitcherTabs&> init_info) :
		value_(make.value.make(SInitInfo{init_info})), switcher_tabs_(&init_info.additional) {
	}
	
	auto SwitcherTabsAction::start_pressed() -> void {
	}
	
	auto SwitcherTabsAction::stop_pressed() -> void {
		value_.set(switcher_tabs_->get_tab(sf::Vector2f(point_position_)));
	}
	
	auto SwitcherTabsAction::while_pressed() -> void {
	}
	
	auto SwitcherTabsAction::while_not_pressed() -> void {
	}
}