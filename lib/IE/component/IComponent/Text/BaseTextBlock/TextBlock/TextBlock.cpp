#include "TextBlock.hpp"

#include <utility>

#include "../../BaseLine/Underline/Underline.hpp"
#include "../../BaseLine/StrikeThrough/StrikeThrough.hpp"

namespace ie {
	TextBlock::Make::Make(
		sf::String text,
		orl::Option<sf::Color> text_color,
		orl::Option<sf::Font&> font,
		orl::Option<sf::Text::Style> style,
		std::vector<BoxPtr<BaseLine::Make> >&& lines,
		orl::Option<size_t> size,
		orl::Option<sf::Color> text_selection_color,
		orl::Option<sf::Color> background_selection_color,
		orl::Option<sf::Color> inactive_text_selection_color,
		orl::Option<sf::Color> inactive_background_selection_color
	) : text(std::move(text)),
	    text_color(std::move(text_color)),
	    font(std::move(font)),
	    style(std::move(style)),
	    lines(std::move(lines)),
	    size(std::move(size)),
	    text_selection_color(std::move(text_selection_color)),
	    background_selection_color(std::move(background_selection_color)),
	    inactive_text_selection_color(std::move(inactive_text_selection_color)),
	    inactive_background_selection_color(std::move(inactive_background_selection_color)) {
	}
	
	auto TextBlock::Make::make(TextBockInitInfo init_info) -> BaseTextBlock* {
		return new TextBlock{std::move(*this), init_info};
	}
	
	auto generate_lines(std::vector<BoxPtr<BaseLine::Make> >&& lines, sf::Text::Style style) -> std::vector<BoxPtr<BaseLine::Make> >&& {
		if(style & sf::Text::Underlined) {
			lines.emplace_back(make_box_ptr<Underline::Make>());
		}
		if(style & sf::Text::StrikeThrough) {
			lines.emplace_back(make_box_ptr<StrikeThrough::Make>());
		}
		return std::move(lines);
	}
	
	TextBlock::TextBlock(Make&& make, TextBockInitInfo init_info) :
		BaseTextBlock(
			{
				std::move(make.text_color).some_or(init_info.text_variables.text_color),
				std::move(make.text_selection_color).some_or(init_info.text_variables.text_selection_color),
				std::move(make.background_selection_color).some_or(init_info.text_variables.background_selection_color),
				std::move(make.inactive_text_selection_color).some_or(init_info.text_variables.inactive_text_selection_color),
				std::move(make.inactive_background_selection_color).some_or(init_info.text_variables.inactive_background_selection_color),
				make.font.some_or(init_info.text_variables.font),
				std::move(make.style).some_or(init_info.text_variables.style),
				std::move(make.size).some_or(init_info.text_variables.size),
			}
		),
		lines_(
			map_make(
				generate_lines(std::move(make.lines), text_variables_.style.some()),
				LineInitInfo{
					text_variables_.size.some(),
					text_variables_.font.some(),
					text_variables_.text_color.some(),
					init_info.text_render_target
				}
			)
		),
		text_(std::move(make.text)) {
		text_characters_.resize(text_.getSize());
		for(auto i{size_t{0}}; i < text_characters_.size(); ++i) {
			text_characters_[i] = make_box_ptr<Character>(text_[i], text_variables_, this->lines_, init_info.text_render_target);
		}
	}
	
	void TextBlock::set_text_variables(
		sf::Color text_color,
		sf::Color text_selection_color,
		sf::Color background_selection_color,
		sf::Color inactive_text_selection_color,
		sf::Color inactive_background_selection_color,
		sf::Font& font,
		size_t size,
		sf::Text::Style style
	) {
		BaseTextBlock::set_text_variables(
			std::move(text_color),
			std::move(text_selection_color),
			std::move(background_selection_color),
			std::move(inactive_text_selection_color),
			std::move(inactive_background_selection_color),
			font,
			std::move(size),
			std::move(style)
		);
		
		text_characters_.resize(text_.getSize());
		for(auto i{size_t{0}}; i < text_characters_.size(); ++i) {
			text_characters_[i] = make_box_ptr<Character>(text_[i], text_variables_, this->lines_, orl::Option<sf::RenderTarget&>{});
		}
	}
	
	auto TextBlock::get_characters() -> std::vector<BaseCharacter*> {
		auto result{std::vector<BaseCharacter*>{text_characters_.size()}};
		for(auto i{size_t{0}}; i < result.size(); ++i) {
			result[i] = text_characters_[i].get();
		}
		return result;
	}
	
	auto TextBlock::update() -> void {
	}
	
	auto TextBlock::handle_event(Event) -> bool {
		return false;
	}
	
	auto TextBlock::in(sf::Vector2f) -> bool {
		return false;
	}
	
	auto TextBlock::set_kerning(char32_t character) -> void {
		for(auto& text_character: text_characters_) {
			text_character->set_kerning(text_variables_.font.some().getKerning(character, text_character->get_char(), text_variables_.size.some()));
			character = text_character->get_char();
		}
	}
	
	auto Determine<TextBlock::Make>::determine(ieml::Node const& node) -> bool {
		return node.is_string();
	}
}

auto ieml::Decode<char, ie::TextBlock::Make>::decode(ieml::Node const& node) -> orl::Option<ie::TextBlock::Make> {
	auto& clear_node{node.get_clear()};
	for(auto& str: clear_node.get_string().ok_or_none()) {
		return {{ie::to_utf32(ie::to_utf32(str))}};
	}
	auto map{clear_node.get_map_view().except()};
	return ie::TextBlock::Make{
		map.at("text").except().as<sf::String>().except(),
		map.get_as<orl::Option<sf::Color> >("text-color").except().ok_or({}),
		map.get_as<orl::Option<sf::Font&> >("font").except().ok_or({}),
		map.get_as<orl::Option<ie::LoadTextStyle> >("style").except().ok_or({}).map([](auto& style) {
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
