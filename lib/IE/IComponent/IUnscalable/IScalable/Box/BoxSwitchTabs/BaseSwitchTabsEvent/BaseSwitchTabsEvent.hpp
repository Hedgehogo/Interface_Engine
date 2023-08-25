#pragma once

#include "../BoxSwitchTabs.hpp"
#include "IE/Interaction/IEvent/BasicKeyEvent/BasicBaseKeyEvent/BasicBaseKeyEvent.hpp"

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
