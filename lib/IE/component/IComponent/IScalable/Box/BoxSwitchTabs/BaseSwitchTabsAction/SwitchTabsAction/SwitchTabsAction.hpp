#pragma once

#include "../../BoxSwitchTabs.hpp"
#include "../BaseSwitchTabsAction.hpp"

namespace ie {
	class SwitchTabsAction : public BaseSwitchTabsAction {
	public:
		struct Make : public virtual BaseSwitchTabsAction::Make {
			size_t index = 0;
			
			Make(size_t index = 0);
			
			SwitchTabsAction* make(BasicActionInitInfo<BoxSwitchTabs&> init_info) override;
		};
		
		SwitchTabsAction(Make&& make, BasicActionInitInfo<BoxSwitchTabs&> init_info);
		
		void init(BasicActionInitInfo<BoxSwitchTabs&> init_info) override;
		
		SwitchTabsAction* copy() override;
	
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		size_t index_;
		ISRSize& value_;
	};
}

template<>
struct ieml::Decode<char, ie::SwitchTabsAction::Make> {
	static orl::Option<ie::SwitchTabsAction::Make> decode(ieml::Node const& node);
};
