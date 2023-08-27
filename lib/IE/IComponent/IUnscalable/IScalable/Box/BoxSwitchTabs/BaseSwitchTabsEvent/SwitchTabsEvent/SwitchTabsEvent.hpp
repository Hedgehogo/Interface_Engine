#pragma once

#include "../../BoxSwitchTabs.hpp"
#include "../BaseSwitchTabsEvent.hpp"

namespace ie {
	class SwitchTabsEvent : public BaseSwitchTabsEvent {
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		SwitchTabsEvent(std::shared_ptr<SValue<uint>> value, uint index);
		
		SwitchTabsEvent* copy() override;
	
	protected:
		uint index;
		PSValue<uint> value;
	};
	
	template<>
	struct DecodePointer<SwitchTabsEvent> {
		static bool decodePointer(const YAML::Node& node, SwitchTabsEvent*& changeObjectEvent);
	};
}
