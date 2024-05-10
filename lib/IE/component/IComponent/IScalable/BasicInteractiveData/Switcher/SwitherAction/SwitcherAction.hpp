#pragma once

#include "IE/utils/bool/ActiveTracker/ActiveTracker.hpp"
#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISReadable/ISReadable.hpp"
#include "IE/interaction/IAction/IBasicTouchAction/IBasicTouchAction.hpp"

namespace ie {
	class Switcher;
	
	class SwitcherAction : public virtual ITouchAction {
	public:
		struct Make : public virtual ITouchAction::Make {
			MakeDyn<ISMBool> value;
			
			Make(MakeDyn<ISMBool> value);
			
			auto make(ActionInitInfo init_info) -> SwitcherAction* override;
		};
		
		SwitcherAction(Make&& make, ActionInitInfo init_info);
		
		SwitcherAction(ISMBool& value);
		
		auto update(orl::Option<Touch> touch) -> void override;
		
	protected:
		ActiveTracker tracker_;
		ISMBool& value_;
	};
}

template<>
struct ieml::Decode<char, ie::SwitcherAction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::SwitcherAction::Make>;
};
