#pragma once

#include "../BoxSwitchTabs.hpp"
#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"

namespace ie {
	class BaseSwitchTabsAction : public BasicBaseKeyAction<BoxSwitchTabs&> {
	public:
		struct Make : public virtual BasicKeyAction<BoxSwitchTabs&>::Make {
			BaseSwitchTabsAction* make(BasicActionInitInfo<BoxSwitchTabs&> init_info) override = 0;
		};
		
		BaseSwitchTabsAction(BasicActionInitInfo<BoxSwitchTabs&> init_info);
		
		BaseSwitchTabsAction();
		
		void init(BasicActionInitInfo<BoxSwitchTabs&> init_info) override;
		
		virtual void set_box(BoxSwitchTabs& box);
		
		virtual BoxSwitchTabs& get_box();
	
	protected:
		BoxSwitchTabs* box;
	};
}