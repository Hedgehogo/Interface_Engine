#pragma once

#include "../../BoxSwitchTabs.hpp"
#include "../BaseSwitchTabsAction.hpp"

namespace ie {
	class SwitchTabsAction : public BaseSwitchTabsAction {
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		SwitchTabsAction(std::shared_ptr<SValue<uint>> value, uint index);
		
		SwitchTabsAction* copy() override;
	
	protected:
		uint index;
		PSValue<uint> value;
	};
	
	template<>
	struct DecodePointer<SwitchTabsAction> {
		static bool decodePointer(const YAML::Node& node, SwitchTabsAction*& changeObjectAction);
	};
}
