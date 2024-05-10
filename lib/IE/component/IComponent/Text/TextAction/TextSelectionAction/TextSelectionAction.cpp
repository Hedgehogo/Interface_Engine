#include "TextSelectionAction.hpp"

#include "IE/component/IComponent/Text/Text.hpp"

#include <cmath>

namespace ie {
	auto TextSelectionAction::Make::make(BasicActionInitInfo<Text&> init_info) -> TextSelectionAction* {
		return new TextSelectionAction{std::move(*this), init_info};
	}
	
	TextSelectionAction::TextSelectionAction(Make&&, BasicActionInitInfo<Text&> init_info) : text_(&init_info.additional), start_(), end_() {
	}
	
	auto TextSelectionAction::get_start() -> orl::Option<std::vector<BaseCharacter*>::iterator> {
		return start_;
	}
	
	auto TextSelectionAction::get_end() -> orl::Option<std::vector<BaseCharacter*>::iterator> {
		return end_;
	}
	
	auto TextSelectionAction::update(sf::Vector2i point_position, bool active) -> void {
		tracker_.update(active);
		for(auto [start_value, end_value]: active && orl::clone(start_) && orl::clone(end_)) {
			if(start_value > end_value) {
				std::swap(start_value, end_value);
			}
			
			for(auto iterator = start_value; iterator != end_value; ++iterator) {
				(*iterator)->set_selection(false);
			}
		}
		
		if(tracker_.started()) {
			text_->set_selection_start(start_ = text_->get_character(sf::Vector2f{point_position}));
		}
		if(tracker_.active()) {
			text_->set_selection_end(end_ = text_->get_character(sf::Vector2f{point_position}));
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
	}
}

auto ieml::Decode<char, ie::TextSelectionAction::Make>::decode(ieml::Node const& node) -> orl::Option<ie::TextSelectionAction::Make> {
	if(node.is_null()) {
		return {{}};
	}
	return {};
}
