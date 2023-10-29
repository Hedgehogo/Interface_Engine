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
		
		SwitchTabsAction(size_t index);
		
		void init(BasicActionInitInfo<BoxSwitchTabs&> init_info) override;
		
		SwitchTabsAction* copy() override;
	
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		size_t index_;
		PSValue<size_t> value_;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<SwitchTabsAction> {
		static bool decode_pointer(const YAML::Node& node, SwitchTabsAction*& change_object_action);
	};
	*/
}
