#pragma once

#include "../../BoxSwitchTabs.hpp"
#include "../BaseSwitchTabsAction.hpp"
#include "../../../../../../../Modules/yaml-cpp/yaml.hpp"

namespace ie {
	class WhileSwitchTabsAction : public BaseSwitchTabsAction {
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		WhileSwitchTabsAction(BoxSwitchTabs* objects = nullptr, int offset = 1);
		
		WhileSwitchTabsAction* copy() override;
	
	protected:
		int objectsSize;
		PSValue<uint> index;
		int offset;
	};
	
	template<>
	struct DecodePointer<WhileSwitchTabsAction> {
		static bool decodePointer(const YAML::Node& node, WhileSwitchTabsAction*& whileChangingObjectsAction);
	};
}
