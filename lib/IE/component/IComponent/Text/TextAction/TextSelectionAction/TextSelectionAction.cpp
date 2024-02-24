#include "TextSelectionAction.hpp"

#include "IE/component/IComponent/Text/Text.hpp"

#include <cmath>

namespace ie {
	TextSelectionAction* TextSelectionAction::Make::make(BasicActionInitInfo<Text&> init_info) {
		return new TextSelectionAction{std::move(*this), init_info};
	}
	
	TextSelectionAction::TextSelectionAction(Make&&, BasicActionInitInfo<Text&> init_info) : text(&init_info.additional), start(), end() {
	}
	
	void TextSelectionAction::start_pressed() {
		text->set_selection_start(start = text->get_character(sf::Vector2f{mouse_position_}));
	}
	
	void TextSelectionAction::stop_pressed() {
	}
	
	void TextSelectionAction::while_pressed() {
		text->set_selection_end(end = text->get_character(sf::Vector2f{mouse_position_}));
		for(auto [local_start, local_end]: start && end) {
			if(start.some() > end.some()) {
				std::swap(local_start, local_end);
			}
			
			for(auto iterator = local_start; iterator != local_end; ++iterator) {
				(*iterator)->set_selection(true);
				(*iterator)->set_active(true);
			}
		}
	}
	
	void TextSelectionAction::while_not_pressed() {
	}
	
	orl::Option<std::vector<BaseCharacter*>::iterator> TextSelectionAction::get_start() {
		return start;
	}
	
	orl::Option<std::vector<BaseCharacter*>::iterator> TextSelectionAction::get_end() {
		return end;
	}
	
	void TextSelectionAction::update(sf::Vector2i mouse_position, bool press) {
		if(press) {
			for(auto [local_start, local_end]: start && end){
				if(start.some() > end.some()) {
					std::swap(local_start, local_end);
				}
				
				for(auto iterator = local_start; iterator != local_end; ++iterator) {
					(*iterator)->set_selection(false);
				}
			}
		}
		BasicBaseKeyAction<Text&>::update(mouse_position, press);
	}
}

orl::Option<ie::TextSelectionAction::Make> ieml::Decode<char, ie::TextSelectionAction::Make>::decode(ieml::Node const& node) {
	if (node.is_null()){
		return ie::TextSelectionAction::Make{};
	}
	return {};
}
