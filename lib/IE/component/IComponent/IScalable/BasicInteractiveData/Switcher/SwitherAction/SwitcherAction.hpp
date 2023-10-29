#pragma once

#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "IE/modules/yaml-cpp/shared/ISValue/SValue/SValue.hpp"

namespace ie {
	class Switcher;
	
	class SwitcherAction : public BaseKeyAction {
	public:
		struct Make : public BaseKeyAction::Make {
			PSbool value;
			
			Make(PSbool value);
			
			SwitcherAction* make(ActionInitInfo init_info) override;
		};
		
		SwitcherAction(Make&& make, ActionInitInfo init_info);
		
		SwitcherAction(PSbool value);
		
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		SwitcherAction* copy() override;
		
	protected:
		PSbool value_;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<SwitcherAction> {
		static bool decode_pointer(const YAML::Node& node, SwitcherAction*& switcher_action);
	};
	*/
	
}