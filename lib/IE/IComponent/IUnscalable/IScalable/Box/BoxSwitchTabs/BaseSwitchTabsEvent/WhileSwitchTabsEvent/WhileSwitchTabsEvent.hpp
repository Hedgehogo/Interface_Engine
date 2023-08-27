#pragma once

#include "../../BoxSwitchTabs.hpp"
#include "../BaseSwitchTabsEvent.hpp"
#include "../../../../../../../Modules/yaml-cpp/yaml.hpp"

namespace ui {
	class WhileSwitchTabsEvent : public BaseSwitchTabsEvent {
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		WhileSwitchTabsEvent(BoxSwitchTabs* objects = nullptr, int offset = 1);
		
		WhileSwitchTabsEvent* copy() override;
	
	protected:
		int objectsSize;
		PSValue<uint> index;
		int offset;
	};
	
	template<>
	struct DecodePointer<WhileSwitchTabsEvent> {
		static bool decodePointer(const YAML::Node& node, WhileSwitchTabsEvent*& whileChangingObjectsEvent);
	};
}
