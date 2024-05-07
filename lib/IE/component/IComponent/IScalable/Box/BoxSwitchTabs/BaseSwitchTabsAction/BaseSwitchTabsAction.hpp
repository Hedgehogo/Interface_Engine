#pragma once

#include "../BoxSwitchTabs.hpp"
#include "IE/interaction/IAction/BasicTouchAction/BasicBaseTouchAction/BasicBaseTouchAction.hpp"

namespace ie {
	class BaseSwitchTabsAction : public BasicBaseTouchAction<BoxSwitchTabs&> {
	public:
		struct Make : public virtual BasicTouchAction<BoxSwitchTabs&>::Make {
			auto make(BasicActionInitInfo<BoxSwitchTabs&> init_info) -> BaseSwitchTabsAction* override = 0;
		};
		
		BaseSwitchTabsAction(BasicActionInitInfo<BoxSwitchTabs&> init_info);
		
		virtual auto set_box(BoxSwitchTabs& box) -> void;
		
		virtual auto get_box() -> BoxSwitchTabs&;
	
	protected:
		BoxSwitchTabs* box_;
	};
}