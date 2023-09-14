#include "TextBlock.hpp"

#include <utility>

#include "../../BaseLine/Underline/Underline.hpp"
#include "../../BaseLine/StrikeThrough/StrikeThrough.hpp"
#include "IE/Modules/yaml-cpp/fileBuffer/fileBuffer.hpp"

namespace ie {
	std::vector<BoxPtr<BaseLine>>&& generateLines(std::vector<BoxPtr<BaseLine>>&& lines, sf::Text::Style style) {
		if(style & sf::Text::Underlined)
			lines.emplace_back(makeBoxPtr<Underline>());
		if(style & sf::Text::StrikeThrough)
			lines.emplace_back(makeBoxPtr<StrikeThrough>());
		return std::move(lines);
	}
	
	TextBlock::TextBlock(
		std::u32string text,
		sf::Color textColor,
		sf::Font* font,
		sf::Text::Style style,
		std::vector<BoxPtr<BaseLine>>&& lines,
		int size,
		sf::Color textSelectionColor,
		sf::Color backgroundSelectionColor,
		sf::Color inactiveTextSelectionColor,
		sf::Color inactiveBackgroundSelectionColor
	) : text(std::move(text)), lines(generateLines(std::move(lines), style)) {
		textVariables.TextColor = textColor;
		textVariables.font = font;
		textVariables.style = style;
		textVariables.size = size;
		textVariables.textSelectionColor = textSelectionColor;
		textVariables.backgroundSelectionColor = backgroundSelectionColor;
		textVariables.inactiveTextSelectionColor = inactiveTextSelectionColor;
		textVariables.inactiveBackgroundSelectionColor = inactiveBackgroundSelectionColor;
	}
	
	TextBlock::TextBlock(std::u32string text, TextVariables textVariables, std::vector<BoxPtr<BaseLine>>&& lines) : BaseTextBlock(textVariables), text(std::move(text)), lines(std::move(lines)) {
	}
	
	void TextBlock::init(InitInfo textInitInfo, InitInfo) {
		for(auto& character: textCharacters) {
			character->init(textInitInfo.renderTarget);
		}
		
		for(auto& line: lines) {
			line->init(textVariables.size, *textVariables.font, textVariables.TextColor, textInitInfo.renderTarget);
		}
	}
	
	void TextBlock::setTextVariables(sf::Color TextColor, sf::Color textSelectionColor, sf::Color backgroundSelectionColor, sf::Color inactiveTextSelectionColor, sf::Color inactiveBackgroundSelectionColor, sf::Font* font, uint size) {
		BaseTextBlock::setTextVariables(TextColor, textSelectionColor, backgroundSelectionColor, inactiveTextSelectionColor, inactiveBackgroundSelectionColor, font, size);
		
		textCharacters.resize(text.size());
		for(std::size_t i = 0; i < textCharacters.size(); ++i) {
			textCharacters[i] = makeBoxPtr<Character>(text[i], textVariables, this->lines);
		}
	}
	
	std::vector<BaseCharacter*> TextBlock::getCharacters() {
		std::vector<BaseCharacter*> result{textCharacters.size()};
		for(int i = 0; i < result.size(); ++i) {
			result[i] = textCharacters[i].get();
		}
		return result;
	}
	
	void TextBlock::update() {
	}
	
	bool TextBlock::updateInteractions(sf::Vector2f) {
		return false;
	}
	
	bool TextBlock::in(sf::Vector2f mousePosition) {
		bool result = true;
		for(auto& character: textCharacters) {
			bool buf = character->in(mousePosition);
			if(!buf)
				result = false;
		}
		return result;
	}
	
	TextBlock* TextBlock::copy() {
		return nullptr;
	}
	
	bool DecodePointer<TextBlock>::decodePointer(const YAML::Node& node, TextBlock*& textBlock) {
		if(node.IsScalar()) {
			textBlock = new TextBlock{node.as<std::u32string>()};
			return true;
		}
		
		std::u32string text;
		sf::Color textColor = nullColor;
		sf::Font* font = nullptr;
		sf::Text::Style style = {};
		std::vector<BaseLine*> lines = {};
		int size = 0;
		sf::Color textSelectionColor = nullColor;
		sf::Color backgroundSelectionColor = nullColor;
		sf::Color inactiveTextSelectionColor = nullColor;
		sf::Color inactiveBackgroundSelectionColor = nullColor;
		
		node["text"] >> text;
		if(node["text-color"])
			node["text-color"] >> textColor;
		if(node["text-color"])
			node["text-color"] >> textColor;
		if(node["font"])
			node["font"] >> font;
		if(node["style"])
			node["style"] >> style;
		if(node["size"])
			node["size"] >> size;
		if(node["text-selection-color"])
			node["text-selection-color"] >> textSelectionColor;
		if(node["background-selection-color"])
			node["background-selection-color"] >> backgroundSelectionColor;
		if(node["inactive-text-selection-color"])
			node["inactive-text-selection-color"] >> inactiveTextSelectionColor;
		if(node["inactive-background-selection-color"])
			node["inactive-background-selection-color"] >> inactiveBackgroundSelectionColor;
		
		if(node["line"]) {
			BaseLine* line;
			node["line"] >> line;
			lines.push_back(line);
		} else if(node["lines"]) {
			for(const YAML::Node& nodeLine: node["lines"]) {
				BaseLine* line;
				nodeLine >> line;
				lines.push_back(line);
			}
		}
		
		{
			textBlock = new TextBlock{
				text,
				textColor,
				font,
				style,
				node["line"] ? makeVector(node["line"].as<BoxPtr<BaseLine>>()) : node["line"].as<std::vector<BoxPtr<BaseLine>>>(),
			    size,
				textSelectionColor,
				backgroundSelectionColor,
				inactiveTextSelectionColor,
				inactiveBackgroundSelectionColor
			};
			return true;
		}
	}
	
	template<>
	bool determine<TextBlock>(const YAML::Node& node) {
		return node.IsScalar();
	}
}
