#pragma once

#include "../BoxSwitchTabs.hpp"
#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"

namespace ie {
	class BaseSwitchTabsAction : public BasicBaseKeyAction<BoxSwitchTabs&> {
	public:
		struct Make : public virtual BasicKeyAction<BoxSwitchTabs&>::Make {
			auto make(BasicActionInitInfo<BoxSwitchTabs&> init_info) -> BaseSwitchTabsAction* override = 0;
		};
		
		BaseSwitchTabsAction(BasicActionInitInfo<BoxSwitchTabs&> init_info);
		
		virtual auto set_box(BoxSwitchTabs& box) -> void;
		
		virtual auto get_box() -> BoxSwitchTabs&;
	
	protected:
		BoxSwitchTabs* box_;
	};
}