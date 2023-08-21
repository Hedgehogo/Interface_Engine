#include "BaseSwitchTabsEvent.hpp"

namespace ui {
	BaseSwitchTabsEvent::BaseSwitchTabsEvent(BoxSwitchTabs* objects) : object(objects) {
	}
	
	void BaseSwitchTabsEvent::setObject(BoxSwitchTabs* object) {
		this->object = object;
	}
	
	BoxSwitchTabs* BaseSwitchTabsEvent::getObject() {
		return object;
	}
}