#pragma once

#include "../BoxSwitchTabs.hpp"
#include "../../../../../../Interaction/IEvent/KeyEvent/BaseKeyEvent/BaseKeyEvent.hpp"

namespace ui {
	class BaseSwitchTabsEvent : public BaseKeyEvent {
	public:
		BaseSwitchTabsEvent(BoxSwitchTabs* objects = nullptr);
		
		virtual void setObject(BoxSwitchTabs* object);
		
		virtual BoxSwitchTabs* getObject();
	
	protected:
		BoxSwitchTabs* object;
	};
}
