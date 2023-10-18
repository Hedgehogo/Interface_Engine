#include "BaseSwitchTabsAction.hpp"

namespace ie {
	BaseSwitchTabsAction::BaseSwitchTabsAction(BasicActionInitInfo<BoxSwitchTabs&> init_info) :
		box(&init_info.additional) {
	}
	
	BaseSwitchTabsAction::BaseSwitchTabsAction() : box(nullptr) {
	}
	
	void BaseSwitchTabsAction::init(BasicActionInitInfo<BoxSwitchTabs&> init_info) {
		box = &init_info.additional;
	}
	
	void BaseSwitchTabsAction::set_box(BoxSwitchTabs& box) {
		this->box = &box;
	}
	
	BoxSwitchTabs& BaseSwitchTabsAction::get_box() {
		return *box;
	}
}