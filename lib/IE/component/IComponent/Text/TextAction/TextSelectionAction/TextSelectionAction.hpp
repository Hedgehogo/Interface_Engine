#pragma once

#include "IE/interaction/IAction/BasicTouchAction/BasicBaseTouchAction/BasicBaseTouchAction.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	class BaseCharacter;
	class Text;
	
	class TextSelectionAction : public BasicBaseTouchAction<Text&> {
	public:
		struct Make : public BasicBaseTouchAction<Text&>::Make {
			auto make(BasicActionInitInfo<Text&> init_info) -> TextSelectionAction* override;
		};
		
		TextSelectionAction(Make&& make, BasicActionInitInfo<Text&> init_info);
		
		auto get_start() -> orl::Option<std::vector<BaseCharacter*>::iterator>;
		
		auto get_end() -> orl::Option<std::vector<BaseCharacter*>::iterator>;
		
		auto update(sf::Vector2i point_position, bool press) -> void override;
		
	protected:
		auto start_pressed() -> void override;
		
		auto stop_pressed() -> void override;
		
		auto while_pressed() -> void override;
		
		auto while_not_pressed() -> void override;
		
		Text* text_;
		orl::Option<std::vector<BaseCharacter*>::iterator> start_, end_;
	};
}

template<>
struct ieml::Decode<char, ie::TextSelectionAction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::TextSelectionAction::Make>;
};