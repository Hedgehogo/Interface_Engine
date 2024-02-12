#include "InteractiveTextBlock.hpp"

#include <utility>

namespace ie {
	InteractiveTextBlock::Make::Make(
		BoxPtr<IBaseInteraction::Make>&& interaction,
		const sf::String& text,
		const orl::Option<sf::Color>& text_color,
		const orl::Option<sf::Font&>& font,
		const orl::Option<sf::Text::Style>& style,
		std::vector<BoxPtr<BaseLine::Make>>&& lines,
		const orl::Option<size_t>& size,
		const orl::Option<sf::Color>& text_selection_color,
		const orl::Option<sf::Color>& background_selection_color,
		const orl::Option<sf::Color>& inactive_text_selection_color,
		const orl::Option<sf::Color>& inactive_background_selection_color
	) : TextBlock::Make(
			text,
			text_color,
			font,
			style,
			std::move(lines),
			size,
			text_selection_color,
			background_selection_color,
			inactive_text_selection_color,
			inactive_background_selection_color
		),
		interaction(std::move(interaction)) {
	}
	
	InteractiveTextBlock* InteractiveTextBlock::Make::make(TextBockInitInfo init_info) {
		return new InteractiveTextBlock{std::move(*this), init_info};
	}
	
	InteractiveTextBlock::InteractiveTextBlock(
		Make&& make,
		TextBockInitInfo init_info
	) : TextBlock(
		TextBlock::Make{
				std::move(make.text),
				make.text_color,
				make.font,
				make.style,
				std::move(make.lines),
				make.size,
				make.text_selection_color,
				make.background_selection_color,
				make.inactive_text_selection_color,
				make.inactive_background_selection_color
			},
		init_info
		),
		interact(false),
		old_interact(false),
		interaction(make.interaction->make({static_cast<InitInfo>(init_info), std::monostate()})) {
		this->interaction_manager = &init_info.text_interaction_manager;
	}
	
	void InteractiveTextBlock::update() {
		if(interact != old_interact) {
			old_interact = interact;
			if(interact) {
				interaction_manager->add_interaction(*interaction);
			} else {
				interaction_manager->delete_interaction(*interaction);
			}
		}
		interact = false;
	}
	
	bool InteractiveTextBlock::update_interactions(sf::Vector2f) {
		interact = true;
		return true;
	}
	
	bool InteractiveTextBlock::in(sf::Vector2f mouse_position) {
		for(auto& character: text_characters) {
			if(character->in(mouse_position)) {
				return true;
			}
		}
		return false;
	}
}

orl::Option<ie::InteractiveTextBlock::Make> ieml::Decode<char, ie::InteractiveTextBlock::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::InteractiveTextBlock::Make{
		map.at("interaction").except().as<bp::BoxPtr<ie::IBaseInteraction::Make> >().except(),
		map.at("text").except().as<sf::String>().except(),
		map.get_as<orl::Option<sf::Color> >("text-color").except().ok_or({}),
		map.get_as<orl::Option<sf::Font&> >("font").except().ok_or({}),
		map.get_as<orl::Option<ie::LoadTextStyle> >("style").except().ok_or({}).map([](auto& style){
			return style.style;
		}),
		map.get_as<std::vector<bp::BoxPtr<ie::BaseLine::Make> > >("lines").except().ok_or({}),
		map.get_as<orl::Option<size_t>>("font-size").except().ok_or({}),
		map.get_as<orl::Option<sf::Color>>("text-selection-color").except().ok_or({}),
		map.get_as<orl::Option<sf::Color>>("background-selection-color").except().ok_or({}),
		map.get_as<orl::Option<sf::Color>>("inactive-text-selection-color").except().ok_or({}),
		map.get_as<orl::Option<sf::Color>>("inactive-background-selection-color").except().ok_or({}),
	};
}
