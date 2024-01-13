#pragma once

#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISValue/ISValue.hpp"
#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"

namespace ie {
	class Switcher;
	
	class SwitcherAction : public BaseKeyAction {
	public:
		struct Make : public BaseKeyAction::Make {
			MakeDyn<ISBool> value;
			
			Make(MakeDyn<ISBool> value);
			
			SwitcherAction* make(ActionInitInfo init_info) override;
		};
		
		SwitcherAction(Make&& make, ActionInitInfo init_info);
		
		SwitcherAction(ISBool& value);
		
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		SwitcherAction* copy() override;
		
	protected:
		ISBool& value_;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<SwitcherAction> {
		static bool decode_pointer(const YAML::Node& node, SwitcherAction*& switcher_action);
	};
	*/
	
}