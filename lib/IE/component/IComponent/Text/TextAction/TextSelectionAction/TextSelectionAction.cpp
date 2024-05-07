#include "TextSelectionAction.hpp"

#include "IE/component/IComponent/Text/Text.hpp"

#include <cmath>

namespace ie {
	auto TextSelectionAction::Make::make(BasicActionInitInfo<Text&> init_info) -> TextSelectionAction* {
		return new TextSelectionAction{std::move(*this), init_info};
	}
	
	TextSelectionAction::TextSelectionAction(Make&&, BasicActionInitInfo<Text&> init_info) : text_(&init_info.additional), start_(), end_() {
	}
	
	auto TextSelectionAction::start_pressed() -> void {
		text_->set_selection_start(start_ = text_->get_character(sf::Vector2f{point_position_}));
	}
	
	auto TextSelectionAction::stop_pressed() -> void {
	}
	
	auto TextSelectionAction::while_pressed() -> void {
		text_->set_selection_end(end_ = text_->get_character(sf::Vector2f{point_position_}));
		for(auto [start_value, end_value]: orl::clone(start_) && orl::clone(end_)) {
			if(start_value > end_value) {
				std::swap(start_value, end_value);
			}
			
			for(auto iterator = start_value; iterator != end_value; ++iterator) {
				(*iterator)->set_selection(true);
				(*iterator)->set_active(true);
			}
		}
	}
	
	auto TextSelectionAction::while_not_pressed() -> void {
	}
	
	auto TextSelectionAction::get_start() -> orl::Option<std::vector<BaseCharacter*>::iterator> {
		return start_;
	}
	
	auto TextSelectionAction::get_end() -> orl::Option<std::vector<BaseCharacter*>::iterator> {
		return end_;
	}
	
	auto TextSelectionAction::update(sf::Vector2i point_position, bool press) -> void {
		for(auto [start_value, end_value]: press && orl::clone(start_) && orl::clone(end_)) {
			if(start_value > end_value) {
				std::swap(start_value, end_value);
			}
			
			for(auto iterator = start_value; iterator != end_value; ++iterator) {
				(*iterator)->set_selection(false);
			}
		}
		BasicBaseTouchAction<Text&>::update(point_position, press);
	}
}

auto ieml::Decode<char, ie::TextSelectionAction::Make>::decode(ieml::Node const& node) -> orl::Option<ie::TextSelectionAction::Make> {
	if(node.is_null()) {
		return {{}};
	}
	return {};
}
