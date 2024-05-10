#pragma once

#include "IE/utils/bool/ActiveTracker/ActiveTracker.hpp"
#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISReadable/ISReadable.hpp"
#include "IE/interaction/IAction/BasicTouchAction/BasicTouchAction.hpp"

namespace ie {
	class Switcher;
	
	class SwitcherAction : public TouchAction {
	public:
		struct Make : public TouchAction::Make {
			MakeDyn<ISMBool> value;
			
			Make(MakeDyn<ISMBool> value);
			
			auto make(ActionInitInfo init_info) -> SwitcherAction* override;
		};
		
		SwitcherAction(Make&& make, ActionInitInfo init_info);
		
		SwitcherAction(ISMBool& value);
		
		auto update(sf::Vector2i point_position, bool active) -> void override;
		
	protected:
		ActiveTracker tracker_;
		ISMBool& value_;
	};
}

template<>
struct ieml::Decode<char, ie::SwitcherAction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::SwitcherAction::Make>;
};
