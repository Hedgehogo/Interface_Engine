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
		
		auto update(bool active) -> void override;
	
	protected:
		size_t size_;
		size_t step_;
		ISMRSize& value_;
	};
}

template<>
struct ieml::Decode<char, ie::WhileSwitchTabsAction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::WhileSwitchTabsAction::Make>;
};
