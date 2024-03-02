#pragma once

#include "../../BoxSwitchTabs.hpp"
#include "../BaseSwitchTabsAction.hpp"

namespace ie {
	class SwitchTabsAction : public BaseSwitchTabsAction {
	public:
		struct Make : public virtual BaseSwitchTabsAction::Make {
			size_t index = 0;
			
			Make(size_t index = 0);
			
			auto make(BasicActionInitInfo<BoxSwitchTabs&> init_info) -> SwitchTabsAction* override;
		};
		
		SwitchTabsAction(Make&& make, BasicActionInitInfo<BoxSwitchTabs&> init_info);
		
	protected:
		auto start_pressed() -> void override;
		
		auto stop_pressed() -> void override;
		
		auto while_pressed() -> void override;
		
		auto while_not_pressed() -> void override;
		
		size_t index_;
		ISMRSize& value_;
	};
}

template<>
struct ieml::Decode<char, ie::SwitchTabsAction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::SwitchTabsAction::Make>;
};
