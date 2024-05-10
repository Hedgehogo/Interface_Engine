#pragma once

#include "IE/utils/bool/ActiveTracker/ActiveTracker.hpp"
#include "IE/shared/ISReadable/ISRanged/ISRanged.hpp"
#include "IE/interaction/IAction/BasicTouchAction/BasicTouchAction.hpp"

namespace ie {
	class BoxSwitcherTabs;
	
	class SwitcherTabsAction : public BasicTouchAction<BoxSwitcherTabs&> {
	public:
		struct Make : public virtual BasicTouchAction<BoxSwitcherTabs&>::Make {
			MakeDyn<ISMRSize> value;
			
			Make(MakeDyn<ISMRSize> value);
			
			auto make(BasicActionInitInfo<BoxSwitcherTabs&> init_info) -> SwitcherTabsAction* override;
		};
		
		SwitcherTabsAction(Make&& make, BasicActionInitInfo<BoxSwitcherTabs&> init_info);
		
		auto update(sf::Vector2i point_position, bool active) -> void override;
		
	protected:
		ActiveTracker tracker_;
		ISMRSize& value_;
		BoxSwitcherTabs* switcher_tabs_;
	};
}