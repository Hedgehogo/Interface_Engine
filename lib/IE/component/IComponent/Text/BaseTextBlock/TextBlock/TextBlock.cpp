#include "TextBlock.hpp"

#include <utility>

#include "../../BaseLine/Underline/Underline.hpp"
#include "../../BaseLine/StrikeThrough/StrikeThrough.hpp"
#include "IE/modules/yaml-cpp/file-buffer/FileBuffer.hpp"

namespace ie {
	TextBlock::Make::Make(
		std::u32string text,
		const orl::Option<sf::Color>& text_color,
		const orl::Option<sf::Font*>& font,
		const orl::Option<sf::Text::Style>& style,
		std::vector<BoxPtr<BaseLine::Make>>&& lines,
		const orl::Option<uint>& size,
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
	
	BaseTextBlock* TextBlock::Make::make(TextBockInitInfo text_block_init_info) {
		return new TextBlock{std::move(*this), text_block_init_info};
	}
	
	std::vector<BoxPtr<BaseLine>>&& generate_lines(std::vector<BoxPtr<BaseLine>>&& lines, sf::Text::Style style) {
		if(style & sf::Text::Underlined)
			lines.emplace_back(make_box_ptr<Underline>());
		if(style & sf::Text::StrikeThrough)
			lines.emplace_back(make_box_ptr<StrikeThrough>());
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
			generate_lines(
				map_make(
					std::move(make.lines),
					LineInitInfo{
						text_variables.size.some(),
						*text_variables.font.some(),
						text_variables.text_color.some(),
						init_info.text_render_target
					}
				),
				text_variables.style.some()
			)
		),
		text(std::move(make.text)) {
		text_characters.resize(text.size());
		for(size_t i = 0; i < text_characters.size(); ++i) {
			text_characters[i] = make_box_ptr<Character>(text[i], text_variables, this->lines, init_info.text_render_target);
		}
	}
	
	TextBlock::TextBlock(
		std::u32string text,
		orl::Option<sf::Color> text_color,
		orl::Option<sf::Font*> font,
		orl::Option<sf::Text::Style> style,
		std::vector<BoxPtr<BaseLine>>&& lines,
		orl::Option<uint> size,
		orl::Option<sf::Color> text_selection_color,
		orl::Option<sf::Color> background_selection_color,
		orl::Option<sf::Color> inactive_text_selection_color,
		orl::Option<sf::Color> inactive_background_selection_color
	) :
		lines(style ? generate_lines(std::move(lines), style.some()) : std::move(lines)), text(std::move(text)) {
		text_variables.text_color = text_color;
		text_variables.font = font;
		text_variables.style = style;
		text_variables.size = size;
		text_variables.text_selection_color = text_selection_color;
		text_variables.background_selection_color = background_selection_color;
		text_variables.inactive_text_selection_color = inactive_text_selection_color;
		text_variables.inactive_background_selection_color = inactive_background_selection_color;
	}
	
	TextBlock::TextBlock(std::u32string text, TextVariables text_variables, std::vector<BoxPtr<BaseLine>>&& lines) :
		BaseTextBlock(text_variables), lines(std::move(lines)), text(std::move(text)) {
	}
	
	void TextBlock::init(TextBockInitInfo text_block_init_info) {
		for(auto& line: lines) {
			line->init(
				{
					text_variables.size.some(),
					*text_variables.font.some(),
					text_variables.text_color.some(),
					text_block_init_info.render_target
				}
			);
		}
	}
	
	void TextBlock::set_text_variables(
		sf::Color TextColor,
		sf::Color text_selection_color,
		sf::Color background_selection_color,
		sf::Color inactive_text_selection_color,
		sf::Color inactive_background_selection_color,
		sf::Font* font,
		uint size,
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
		
		text_characters.resize(text.size());
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
	
	bool TextBlock::in(sf::Vector2f mouse_position) {
		bool result = true;
		for(auto& character: text_characters) {
			bool buf = character->in(mouse_position);
			if(!buf)
				result = false;
		}
		return result;
	}
	
	void TextBlock::set_kerning(char32_t character) {
		for(auto& text_character : text_characters){
			text_character->set_kerning(text_variables.font.some()->getKerning(character, text_character->get_char(), text_variables.size.some()));
			character = text_character->get_char();
		}
	}
	
	TextBlock* TextBlock::copy() {
		return nullptr;
	}
	
	bool DecodePointer<TextBlock>::decode_pointer(const YAML::Node& node, TextBlock*& text_block) {
		if(node.IsScalar()) {
			text_block = new TextBlock{node.as<std::u32string>()};
		} else {
			text_block = new TextBlock{
				node["text"].as<std::u32string>(),
				conv_def<orl::Option<sf::Color> >(node["text-color"], {}),
				conv_def<orl::Option<sf::Font*> >(node["font"], {}),
				conv_def<orl::Option<sf::Text::Style> >(node["style"], {}),
				node["line"] ? make_vector(node["line"].as<BoxPtr<BaseLine > >()) : node["line"].as<std::vector<BoxPtr<BaseLine> > >(),
				conv_def<orl::Option<uint> >(node["size"], {}),
				conv_def<orl::Option<sf::Color> >(node["text-selection-color"], {}),
				conv_def<orl::Option<sf::Color> >(node["background-selection-color"], {}),
				conv_def<orl::Option<sf::Color> >(node["inactive-text-selection-color"], {}),
				conv_def<orl::Option<sf::Color> >(node["inactive-background-selection-color"], {})
			};
		}
		return true;
	}
	
	template<>
	bool determine<TextBlock>(const YAML::Node& node) {
		return node.IsScalar();
	}
}