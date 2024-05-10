#include "TextSelectionAction.hpp"

#include "IE/component/IComponent/Text/Text.hpp"

#include <cmath>

namespace ie {
	auto TextSelectionAction::Make::make(BasicActionInitInfo<Text&> init_info) -> TextSelectionAction* {
		return new TextSelectionAction{std::move(*this), init_info};
	}
	
	TextSelectionAction::TextSelectionAction(Make&&, BasicActionInitInfo<Text&> init_info) :
		active(false), text_(&init_info.additional), start_(), end_() {
	}
	
	auto TextSelectionAction::get_start() -> orl::Option<std::vector<BaseCharacter*>::iterator> {
		return start_;
	}
	
	auto TextSelectionAction::get_end() -> orl::Option<std::vector<BaseCharacter*>::iterator> {
		return end_;
	}
	
	auto TextSelectionAction::update(orl::Option<Touch> touch) -> void {
		auto const pressing{Touch::pressing(touch)};
		for(auto [start_value, end_value]: pressing.is_some() && orl::clone(start_) && orl::clone(end_)) {
			if(start_value > end_value) {
				std::swap(start_value, end_value);
			}
			
			for(auto iterator = start_value; iterator != end_value; ++iterator) {
				(*iterator)->set_selection(false);
			}
		}
		
		for(auto const point_position: pressing) {
			if(!active) {
				text_->set_selection_start(start_ = text_->get_character(sf::Vector2f{point_position}));
			}
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
		active = pressing.is_some();
	}
}

auto ieml::Decode<char, ie::TextSelectionAction::Make>::decode(ieml::Node const& node) -> orl::Option<ie::TextSelectionAction::Make> {
	if(node.is_null()) {
		return {{}};
	}
	return {};
}
