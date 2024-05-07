#pragma once

#include "IE/shared/ISReadable/ISRanged/ISRanged.hpp"
#include "IE/interaction/IAction/BasicTouchAction/BasicBaseTouchAction/BasicBaseTouchAction.hpp"

namespace ie {
	class BoxSwitcherTabs;
	
	class SwitcherTabsAction : public BasicBaseTouchAction<BoxSwitcherTabs&> {
	public:
		struct Make : public virtual BasicTouchAction<BoxSwitcherTabs&>::Make {
			MakeDyn<ISMRSize> value;
			
			Make(MakeDyn<ISMRSize> value);
			
			auto make(BasicActionInitInfo<BoxSwitcherTabs&> init_info) -> SwitcherTabsAction* override;
		};
		
		SwitcherTabsAction(Make&& make, BasicActionInitInfo<BoxSwitcherTabs&> init_info);
		
		auto start_pressed() -> void override;
		
		auto stop_pressed() -> void override;
		
		auto while_pressed() -> void override;
		
		auto while_not_pressed() -> void override;
		
	protected:
		ISMRSize& value_;
		BoxSwitcherTabs* switcher_tabs_;
	};
}