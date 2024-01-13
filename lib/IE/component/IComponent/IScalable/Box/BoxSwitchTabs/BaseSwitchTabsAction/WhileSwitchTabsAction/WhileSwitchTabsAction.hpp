#pragma once

#include "../../BoxSwitchTabs.hpp"
#include "../BaseSwitchTabsAction.hpp"
#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	class WhileSwitchTabsAction : public BaseSwitchTabsAction {
	public:
		struct Make : public virtual BaseSwitchTabsAction::Make {
			int step = 1;
			
			Make(int step = 1);
			
			WhileSwitchTabsAction* make(BasicActionInitInfo<BoxSwitchTabs&> init_info) override;
		};
		
		WhileSwitchTabsAction(Make&& make, BasicActionInitInfo<BoxSwitchTabs&> init_info);
		
		void init(BasicActionInitInfo<BoxSwitchTabs&> init_info) override;
		
		WhileSwitchTabsAction* copy() override;
	
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		int size_;
		ISRSize& value_;
		int step_;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<WhileSwitchTabsAction> {
		static bool decode_pointer(const YAML::Node& node, WhileSwitchTabsAction*& while_changing_objects_action);
	};
	*/
}