#pragma once

#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISReadable/ISReadable.hpp"
#include "IE/interaction/IAction/BasicTouchAction/BasicBaseTouchAction/BasicBaseTouchAction.hpp"

namespace ie {
	class Switcher;
	
	class SwitcherAction : public BaseTouchAction {
	public:
		struct Make : public BaseTouchAction::Make {
			MakeDyn<ISMBool> value;
			
			Make(MakeDyn<ISMBool> value);
			
			auto make(ActionInitInfo init_info) -> SwitcherAction* override;
		};
		
		SwitcherAction(Make&& make, ActionInitInfo init_info);
		
		SwitcherAction(ISMBool& value);
		
		auto start_pressed() -> void override;
		
		auto stop_pressed() -> void override;
		
		auto while_pressed() -> void override;
		
		auto while_not_pressed() -> void override;
		
	protected:
		ISMBool& value_;
	};
}

template<>
struct ieml::Decode<char, ie::SwitcherAction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::SwitcherAction::Make>;
};
