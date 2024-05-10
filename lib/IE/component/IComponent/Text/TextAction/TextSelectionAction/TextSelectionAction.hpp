#pragma once

#include "IE/utils/bool/ActiveTracker/ActiveTracker.hpp"
#include "IE/interaction/IAction/IBasicTouchAction/IBasicTouchAction.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	class BaseCharacter;
	class Text;
	
	class TextSelectionAction : public virtual IBasicTouchAction<Text&> {
	public:
		struct Make : public virtual IBasicTouchAction<Text&>::Make {
			auto make(BasicActionInitInfo<Text&> init_info) -> TextSelectionAction* override;
		};
		
		TextSelectionAction(Make&& make, BasicActionInitInfo<Text&> init_info);
		
		auto get_start() -> orl::Option<std::vector<BaseCharacter*>::iterator>;
		
		auto get_end() -> orl::Option<std::vector<BaseCharacter*>::iterator>;
		
		auto update(orl::Option<Touch> touch) -> void override;
		
	protected:
		bool active;
		Text* text_;
		orl::Option<std::vector<BaseCharacter*>::iterator> start_, end_;
	};
}

template<>
struct ieml::Decode<char, ie::TextSelectionAction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::TextSelectionAction::Make>;
};