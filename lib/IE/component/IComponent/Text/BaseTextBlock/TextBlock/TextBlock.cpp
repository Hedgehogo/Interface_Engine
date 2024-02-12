#include "TextBlock.hpp"

#include <utility>

#include "../../BaseLine/Underline/Underline.hpp"
#include "../../BaseLine/StrikeThrough/StrikeThrough.hpp"

namespace ie {
	TextBlock::Make::Make(
		sf::String text,
		const orl::Option<sf::Color>& text_color,
		const orl::Option<sf::Font&>& font,
		const orl::Option<sf::Text::Style>& style,
		std::vector<BoxPtr<BaseLine::Make>>&& lines,
		const orl::Option<size_t>& size,
		const orl::Option<sf::Color>& text_selection_color,
		const orl::Option<sf::Color>& background_selection_color,
		const orl::Option<sf::Color>& inactive_text_selection_color,
		const orl::Option<sf::Color>& inactive_background_selection_color
	) : text(std::move(text)),
		text_color(text_color),
		font(font),
		style(style),
		lines(std::move(lines)),
		size(size),
		text_selection_color(text_selection_color),
		background_selection_color(background_selection_color),
		inactive_text_selection_color(inactive_text_selection_color),
		inactive_background_selection_color(inactive_background_selection_color) {
	}
	
	BaseTextBlock* TextBlock::Make::make(TextBockInitInfo init_info) {
		return new TextBlock{std::move(*this), init_info};
	}
	
	std::vector<BoxPtr<BaseLine::Make>>&& generate_lines(std::vector<BoxPtr<BaseLine::Make>>&& lines, sf::Text::Style style) {
		if(style & sf::Text::Underlined)
			lines.emplace_back(make_box_ptr<Underline::Make>());
		if(style & sf::Text::StrikeThrough)
			lines.emplace_back(make_box_ptr<StrikeThrough::Make>());
		return std::move(lines);
	}
	
	TextBlock::TextBlock(Make&& make, TextBockInitInfo init_info) :
		BaseTextBlock(
			{
				make.text_color.some_or(init_info.text_variables.text_color),
				make.text_selection_color.some_or(init_info.text_variables.text_selection_color),
				make.background_selection_color.some_or(init_info.text_variables.background_selection_color),
				make.inactive_text_selection_color.some_or(init_info.text_variables.inactive_text_selection_color),
				make.inactive_background_selection_color.some_or(init_info.text_variables.inactive_background_selection_color),
				make.font.some_or(init_info.text_variables.font),
				make.style.some_or(init_info.text_variables.style),
				make.size.some_or(init_info.text_variables.size),
			}
		),
		lines(
			map_make(
				generate_lines(
				std::move(make.lines),
				text_variables.style.some()
				),
				LineInitInfo{
					text_variables.size.some(),
					text_variables.font.some(),
					text_variables.text_color.some(),
					init_info.text_render_target
				}
			)
		),
		text(std::move(make.text)) {
		text_characters.resize(text.getSize());
		for(size_t i = 0; i < text_characters.size(); ++i) {
			text_characters[i] = make_box_ptr<Character>(text[i], text_variables, this->lines, init_info.text_render_target);
		}
	}
	
	void TextBlock::set_text_variables(
		sf::Color TextColor,
		sf::Color text_selection_color,
		sf::Color background_selection_color,
		sf::Color inactive_text_selection_color,
		sf::Color inactive_background_selection_color,
		sf::Font& font,
		size_t size,
		sf::Text::Style style
	) {
		BaseTextBlock::set_text_variables(
			TextColor,
			text_selection_color,
			background_selection_color,
			inactive_text_selection_color,
			inactive_background_selection_color,
			font,
			size,
			style
		);
		
		text_characters.resize(text.getSize());
		for(size_t i = 0; i < text_characters.size(); ++i) {
			text_characters[i] = make_box_ptr<Character>(text[i], text_variables, this->lines, orl::Option<sf::RenderTarget&> {});
		}
	}
	
	std::vector<BaseCharacter*> TextBlock::get_characters() {
		std::vector<BaseCharacter*> result{text_characters.size()};
		for(size_t i = 0; i < result.size(); ++i) {
			result[i] = text_characters[i].get();
		}
		return result;
	}
	
	void TextBlock::update() {
	}
	
	bool TextBlock::update_interactions(sf::Vector2f) {
		return false;
	}
	
	bool TextBlock::in(sf::Vector2f) {
		return false;
	}
	
	void TextBlock::set_kerning(char32_t character) {
		for(auto& text_character : text_characters){
			text_character->set_kerning(text_variables.font.some().getKerning(character, text_character->get_char(), text_variables.size.some()));
			character = text_character->get_char();
		}
	}
	
	bool Determine<TextBlock::Make>::determine(const ieml::Node& node) {
		return node.is_string();
	}
}

orl::Option<ie::TextBlock::Make> ieml::Decode<char, ie::TextBlock::Make>::decode(ieml::Node const& node) {
	auto& clear_node{node.get_clear()};
	if (auto str{clear_node.get_string()}){
		return {{ie::to_utf32(ie::to_utf32(str.except()))}};
	}
	auto map{clear_node.get_map_view().except()};
	return ie::TextBlock::Make{
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
