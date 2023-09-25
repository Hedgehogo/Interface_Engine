#include "BaseSwitchTabsAction.hpp"

namespace ie {
	BaseSwitchTabsAction::BaseSwitchTabsAction(BasicActionInitInfo<BoxSwitchTabs&> initInfo) :
		box(&initInfo.additional) {
	}
	
	BaseSwitchTabsAction::BaseSwitchTabsAction() : box(nullptr) {
	}
	
	void BaseSwitchTabsAction::init(BasicActionInitInfo<BoxSwitchTabs&> initInfo) {
		box = &initInfo.additional;
	}
	
	void BaseSwitchTabsAction::setBox(BoxSwitchTabs& box) {
		this->box = &box;
	}
	
	BoxSwitchTabs& BaseSwitchTabsAction::getBox() {
		return *box;
	}
}