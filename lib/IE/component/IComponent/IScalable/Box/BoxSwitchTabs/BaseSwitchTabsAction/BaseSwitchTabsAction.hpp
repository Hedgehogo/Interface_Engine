#pragma once

#include "../BoxSwitchTabs.hpp"
#include "IE/interaction/IAction/IBasicAction/IBasicAction.hpp"

namespace ie {
	class BaseSwitchTabsAction : public virtual IBasicAction<BoxSwitchTabs&> {
	public:
		struct Make : public virtual IBasicAction<BoxSwitchTabs&>::Make {
			auto make(BasicActionInitInfo<BoxSwitchTabs&> init_info) -> BaseSwitchTabsAction* override = 0;
		};
		
		BaseSwitchTabsAction(BasicActionInitInfo<BoxSwitchTabs&> init_info);
		
		virtual auto set_box(BoxSwitchTabs& box) -> void;
		
		virtual auto get_box() -> BoxSwitchTabs&;
	
	protected:
		BoxSwitchTabs* box_;
	};
}