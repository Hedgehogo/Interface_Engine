#include "InteractiveTextBlock.hpp"

#include <utility>

namespace ie {
	InteractiveTextBlock::Make::Make(
		BoxPtr<IBaseInteraction::Make>&& interaction,
		sf::String const& text,
		orl::Option<sf::Color> text_color,
		orl::Option<sf::Font&> font,
		orl::Option<sf::Text::Style> style,
		std::vector<BoxPtr<BaseLine::Make> >&& lines,
		orl::Option<size_t> size,
		orl::Option<sf::Color> text_selection_color,
		orl::Option<sf::Color> background_selection_color,
		orl::Option<sf::Color> inactive_text_selection_color,
		orl::Option<sf::Color> inactive_background_selection_color
	) :
		TextBlock::Make(
			text,
			std::move(text_color),
			std::move(font),
			std::move(style),
			std::move(lines),
			std::move(size),
			std::move(text_selection_color),
			std::move(background_selection_color),
			std::move(inactive_text_selection_color),
			std::move(inactive_background_selection_color)
		),
		interaction(std::move(interaction)) {
	}
	
	auto InteractiveTextBlock::Make::make(TextBockInitInfo init_info) -> InteractiveTextBlock* {
		return new InteractiveTextBlock{std::move(*this), init_info};
	}
	
	InteractiveTextBlock::InteractiveTextBlock(
		Make&& make,
		TextBockInitInfo init_info
	) :
		TextBlock(
			TextBlock::Make{
				std::move(make.text),
				std::move(make.text_color),
				std::move(make.font),
				std::move(make.style),
				std::move(make.lines),
				std::move(make.size),
				std::move(make.text_selection_color),
				std::move(make.background_selection_color),
				std::move(make.inactive_text_selection_color),
				std::move(make.inactive_background_selection_color)
			},
			init_info
		),
		interaction_(make.interaction->make({static_cast<InitInfo>(init_info), {}})),
		interaction_manager_(&init_info.text_interaction_manager) {
	}
	
	auto InteractiveTextBlock::update() -> void {
		interaction_->update();
	}
	
	auto InteractiveTextBlock::handle_event(Event event) -> bool {
		return interaction_->handle_event(event);
	}
	
	auto InteractiveTextBlock::in(sf::Vector2f point_position) -> bool {
		for(auto& character: text_characters_) {
			if(character->in(point_position)) {
				return true;
			}
		}
		return false;
	}
}

auto ieml::Decode<char, ie::InteractiveTextBlock::Make>::decode(ieml::Node const& node) -> orl::Option<ie::InteractiveTextBlock::Make> {
	auto map{node.get_map_view().except()};
	return ie::InteractiveTextBlock::Make{
		map.at("interaction").except().as<bp::BoxPtr<ie::IBaseInteraction::Make> >().except(),
		map.at("text").except().as<sf::String>().except(),
		map.get_as<orl::Option<sf::Color> >("text-color").except().ok_or({}),
		map.get_as<orl::Option<sf::Font&> >("font").except().ok_or({}),
		map.get_as<orl::Option<ie::LoadTextStyle> >("style").except().ok_or({}).map([](auto&& style) {
			return style.style;
		}),
		map.get_as<std::vector<bp::BoxPtr<ie::BaseLine::Make> > >("lines").except().ok_or({}),
		map.get_as<orl::Option<size_t> >("font-size").except().ok_or({}),
		map.get_as<orl::Option<sf::Color> >("text-selection-color").except().ok_or({}),
		map.get_as<orl::Option<sf::Color> >("background-selection-color").except().ok_or({}),
		map.get_as<orl::Option<sf::Color> >("inactive-text-selection-color").except().ok_or({}),
		map.get_as<orl::Option<sf::Color> >("inactive-background-selection-color").except().ok_or({}),
	};
}
