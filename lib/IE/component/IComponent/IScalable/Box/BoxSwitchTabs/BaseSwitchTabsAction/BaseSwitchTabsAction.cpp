#include "BaseSwitchTabsAction.hpp"

namespace ie {
	BaseSwitchTabsAction::BaseSwitchTabsAction(BasicActionInitInfo<BoxSwitchTabs&> init_info) :
		box_(&init_info.additional) {
	}
	
	auto BaseSwitchTabsAction::set_box(BoxSwitchTabs& box) -> void {
		this->box_ = &box;
	}
	
	auto BaseSwitchTabsAction::get_box() -> BoxSwitchTabs& {
		return *box_;
	}
}