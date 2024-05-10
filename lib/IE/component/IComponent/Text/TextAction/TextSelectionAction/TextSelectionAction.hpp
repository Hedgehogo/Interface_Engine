#pragma once

#include "IE/utils/bool/ActiveTracker/ActiveTracker.hpp"
#include "IE/interaction/IAction/BasicTouchAction/BasicTouchAction.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	class BaseCharacter;
	class Text;
	
	class TextSelectionAction : public BasicTouchAction<Text&> {
	public:
		struct Make : public BasicTouchAction<Text&>::Make {
			auto make(BasicActionInitInfo<Text&> init_info) -> TextSelectionAction* override;
		};
		
		TextSelectionAction(Make&& make, BasicActionInitInfo<Text&> init_info);
		
		auto get_start() -> orl::Option<std::vector<BaseCharacter*>::iterator>;
		
		auto get_end() -> orl::Option<std::vector<BaseCharacter*>::iterator>;
		
		auto update(sf::Vector2i point_position, bool active) -> void override;
		
	protected:
		ActiveTracker tracker_;
		Text* text_;
		orl::Option<std::vector<BaseCharacter*>::iterator> start_, end_;
	};
}

template<>
struct ieml::Decode<char, ie::TextSelectionAction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::TextSelectionAction::Make>;
};