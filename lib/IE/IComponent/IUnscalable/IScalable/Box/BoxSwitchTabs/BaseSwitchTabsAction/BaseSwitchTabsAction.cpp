#include "BaseSwitchTabsAction.hpp"

namespace ie {
	BaseSwitchTabsAction::BaseSwitchTabsAction(BoxSwitchTabs* objects) : object(objects) {
	}
	
	void BaseSwitchTabsAction::setObject(BoxSwitchTabs* object) {
		this->object = object;
	}
	
	BoxSwitchTabs* BaseSwitchTabsAction::getObject() {
		return object;
	}
}