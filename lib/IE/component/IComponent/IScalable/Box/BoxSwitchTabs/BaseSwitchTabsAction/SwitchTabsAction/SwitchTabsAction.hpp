#pragma once

#include "../../BoxSwitchTabs.hpp"
#include "../BaseSwitchTabsAction.hpp"

namespace ie {
	class SwitchTabsAction : public BaseSwitchTabsAction {
	public:
		struct Make : public virtual BaseSwitchTabsAction::Make {
			uint index = 0;
			
			Make(uint index = 0);
			
			SwitchTabsAction* make(BasicActionInitInfo<BoxSwitchTabs&> init_info) override;
		};
		
		SwitchTabsAction(Make&& make, BasicActionInitInfo<BoxSwitchTabs&> init_info);
		
		SwitchTabsAction(uint index);
		
		void init(BasicActionInitInfo<BoxSwitchTabs&> init_info) override;
		
		SwitchTabsAction* copy() override;
	
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		uint index;
		PSValue<uint> value;
	};
	
	template<>
	struct DecodePointer<SwitchTabsAction> {
		static bool decode_pointer(const YAML::Node& node, SwitchTabsAction*& change_object_action);
	};
}
