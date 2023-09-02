#pragma once

#include "../../BoxSwitchTabs.hpp"
#include "../BaseSwitchTabsAction.hpp"
#include "../../../../../../../Modules/yaml-cpp/yaml.hpp"

namespace ie {
	class WhileSwitchTabsAction : public BaseSwitchTabsAction {
	public:
		struct Make : public BaseSwitchTabsAction::Make {
			int step = 1;
			
			Make(int step = 1);
			
			WhileSwitchTabsAction* make(BasicActionInitInfo<BoxSwitchTabs&> initInfo) override;
		};
		
		WhileSwitchTabsAction(Make&& make, BasicActionInitInfo<BoxSwitchTabs&> initInfo);
		
		WhileSwitchTabsAction(int step = 1);
		
		void init(BasicActionInitInfo<BoxSwitchTabs&> initInfo) override;
		
		WhileSwitchTabsAction* copy() override;
	
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		int size;
		PSValue<uint> value;
		int step;
	};
	
	template<>
	struct DecodePointer<WhileSwitchTabsAction> {
		static bool decodePointer(const YAML::Node& node, WhileSwitchTabsAction*& whileChangingObjectsAction);
	};
}
