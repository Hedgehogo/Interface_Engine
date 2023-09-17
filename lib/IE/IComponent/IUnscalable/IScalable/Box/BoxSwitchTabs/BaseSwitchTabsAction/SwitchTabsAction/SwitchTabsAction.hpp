#pragma once

#include "../../BoxSwitchTabs.hpp"
#include "../BaseSwitchTabsAction.hpp"

namespace ie {
	class SwitchTabsAction : public BaseSwitchTabsAction {
	public:
		struct Make : public virtual BaseSwitchTabsAction::Make {
			uint index = 0;
			
			Make(uint index = 0);
			
			SwitchTabsAction* make(BasicActionInitInfo<BoxSwitchTabs&> initInfo) override;
		};
		
		SwitchTabsAction(Make&& make, BasicActionInitInfo<BoxSwitchTabs&> initInfo);
		
		SwitchTabsAction(uint index);
		
		void init(BasicActionInitInfo<BoxSwitchTabs&> initInfo) override;
		
		SwitchTabsAction* copy() override;
	
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		uint index;
		PSValue<uint> value;
	};
	
	template<>
	struct DecodePointer<SwitchTabsAction> {
		static bool decodePointer(const YAML::Node& node, SwitchTabsAction*& changeObjectAction);
	};
}
