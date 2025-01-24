#pragma once

#include "../BoxSwitchTabs.hpp"
#include "IE/trigger/IAction/IBasicActivityAction/IBasicActivityAction.hpp"

namespace ie {
	class BaseSwitchTabsAction : public virtual IBasicActivityAction<BoxSwitchTabs&> {
	public:
		struct Make : public virtual IBasicActivityAction<BoxSwitchTabs&>::Make {
			auto make(BasicActionInitInfo<BoxSwitchTabs&> init_info) -> BaseSwitchTabsAction* override = 0;
		};
		
		BaseSwitchTabsAction(BasicActionInitInfo<BoxSwitchTabs&> init_info);
		
		virtual auto set_box(BoxSwitchTabs& box) -> void;
		
		virtual auto get_box() -> BoxSwitchTabs&;
	
	protected:
		BoxSwitchTabs* box_;
	};
}