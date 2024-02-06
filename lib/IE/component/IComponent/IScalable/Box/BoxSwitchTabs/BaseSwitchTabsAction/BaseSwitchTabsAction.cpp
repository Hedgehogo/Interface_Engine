#include "BaseSwitchTabsAction.hpp"

namespace ie {
	BaseSwitchTabsAction::BaseSwitchTabsAction(BasicActionInitInfo<BoxSwitchTabs&> init_info) :
		box_(&init_info.additional) {
	}
	
	void BaseSwitchTabsAction::set_box(BoxSwitchTabs& box) {
		this->box_ = &box;
	}
	
	BoxSwitchTabs& BaseSwitchTabsAction::get_box() {
		return *box_;
	}
}