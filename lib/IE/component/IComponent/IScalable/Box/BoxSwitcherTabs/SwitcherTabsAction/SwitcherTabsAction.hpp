#pragma once

#include "IE/utils/bool/ActiveTracker/ActiveTracker.hpp"
#include "IE/shared/ISReadable/ISRanged/ISRanged.hpp"
#include "IE/interaction/IAction/IBasicTouchAction/IBasicTouchAction.hpp"

namespace ie {
	class BoxSwitcherTabs;
	
	class SwitcherTabsAction : public virtual IBasicTouchAction<BoxSwitcherTabs&> {
	public:
		struct Make : public virtual IBasicTouchAction<BoxSwitcherTabs&>::Make {
			MakeDyn<ISMRSize> value;
			
			Make(MakeDyn<ISMRSize> value);
			
			auto make(BasicActionInitInfo<BoxSwitcherTabs&> init_info) -> SwitcherTabsAction* override;
		};
		
		SwitcherTabsAction(Make&& make, BasicActionInitInfo<BoxSwitcherTabs&> init_info);
		
		auto update(orl::Option<Touch> touch) -> void override;
		
	protected:
		orl::Option<sf::Vector2f> pressing;
		ActiveTracker tracker_;
		ISMRSize& value_;
		BoxSwitcherTabs* switcher_tabs_;
	};
}