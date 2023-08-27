#include "BaseSwitchTabsEvent.hpp"

namespace ie {
	BaseSwitchTabsEvent::BaseSwitchTabsEvent(BoxSwitchTabs* objects) : object(objects) {
	}
	
	void BaseSwitchTabsEvent::setObject(BoxSwitchTabs* object) {
		this->object = object;
	}
	
	BoxSwitchTabs* BaseSwitchTabsEvent::getObject() {
		return object;
	}
}