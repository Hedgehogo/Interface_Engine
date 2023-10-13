#pragma once

#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "IE/modules/yaml-cpp/shared/value/general/sValue.hpp"

namespace ie {
	class Switcher;
	
	class SwitcherAction : public BaseKeyAction {
	public:
		struct Make : public BaseKeyAction::Make {
			PSbool value;
			
			Make(PSbool value);
			
			SwitcherAction* make(ActionInitInfo initInfo) override;
		};
		
		SwitcherAction(Make&& make, ActionInitInfo initInfo);
		
		SwitcherAction(PSbool value);
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		SwitcherAction* copy() override;
		
	protected:
		PSbool value;
	};
	
	template<>
	struct DecodePointer<SwitcherAction> {
		static bool decodePointer(const YAML::Node& node, SwitcherAction*& switcherAction);
	};
	
}