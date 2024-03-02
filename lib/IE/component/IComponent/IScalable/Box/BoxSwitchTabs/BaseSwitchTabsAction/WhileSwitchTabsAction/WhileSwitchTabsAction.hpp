#pragma once

#include "../../BoxSwitchTabs.hpp"
#include "../BaseSwitchTabsAction.hpp"

namespace ie {
	class WhileSwitchTabsAction : public BaseSwitchTabsAction {
	public:
		struct Make : public virtual BaseSwitchTabsAction::Make {
			int step = 1;
			
			Make(int step = 1);
			
			auto make(BasicActionInitInfo<BoxSwitchTabs&> init_info) -> WhileSwitchTabsAction* override;
		};
		
		WhileSwitchTabsAction(Make&& make, BasicActionInitInfo<BoxSwitchTabs&> init_info);
		
	protected:
		auto start_pressed() -> void override;
		
		auto stop_pressed() -> void override;
		
		auto while_pressed() -> void override;
		
		auto while_not_pressed() -> void override;
		
		int size_;
		ISMRSize& value_;
		int step_;
	};
}

template<>
struct ieml::Decode<char, ie::WhileSwitchTabsAction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::WhileSwitchTabsAction::Make>;
};
