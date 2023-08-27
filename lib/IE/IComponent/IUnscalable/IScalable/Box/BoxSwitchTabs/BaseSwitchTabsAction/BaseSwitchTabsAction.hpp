#pragma once

#include "../BoxSwitchTabs.hpp"
#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"

namespace ie {
	class BaseSwitchTabsAction : public BaseKeyAction {
	public:
		BaseSwitchTabsAction(BoxSwitchTabs* objects = nullptr);
		
		virtual void setObject(BoxSwitchTabs* object);
		
		virtual BoxSwitchTabs* getObject();
	
	protected:
		BoxSwitchTabs* object;
	};
}
