#pragma once

#include "../BoxSwitchTabs.hpp"
#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"

namespace ie {
	class BaseSwitchTabsAction : public BasicBaseKeyAction<BoxSwitchTabs&> {
	public:
		struct Make : public virtual BasicKeyAction<BoxSwitchTabs&>::Make {
			BaseSwitchTabsAction* make(BasicActionInitInfo<BoxSwitchTabs&> initInfo) override = 0;
		};
		
		BaseSwitchTabsAction(BasicActionInitInfo<BoxSwitchTabs&> initInfo);
		
		BaseSwitchTabsAction();
		
		void init(BasicActionInitInfo<BoxSwitchTabs&> initInfo) override;
		
		virtual void setBox(BoxSwitchTabs& box);
		
		virtual BoxSwitchTabs& getBox();
	
	protected:
		BoxSwitchTabs* box;
	};
}
