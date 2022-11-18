#include "textBlock.hpp"

#include "../../line/underline/underline.hpp"
#include "../../line/strikeThrough/strikeThrough.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/fileBuffer/fileBuffer.hpp"

namespace ui {
	std::vector<BaseLine *> generateLines(std::vector<BaseLine *> lines, sf::Text::Style style) {
		if(style & sf::Text::Underlined)
			lines.push_back(new Underline);
		if(style & sf::Text::StrikeThrough)
			lines.push_back(new StrikeThrough);
		return lines;
	}
	
	TextBlock::TextBlock(std::u32string text, sf::Color textColor, sf::Font *font, sf::Text::Style style, std::vector<BaseLine *> lines, int size, sf::Color textSelectionColor, sf::Color backgroundSelectionColor,
						 sf::Color inactiveTextSelectionColor, sf::Color inactiveBackgroundSelectionColor) :
		str(text), lines(generateLines(lines, style)) {
		
		textVariables.TextColor = textColor;
		textVariables.font = font;
		textVariables.style = style;
		textVariables.size = size;
		textVariables.textSelectionColor = textSelectionColor;
		textVariables.backgroundSelectionColor = backgroundSelectionColor;
		textVariables.inactiveTextSelectionColor = inactiveTextSelectionColor;
		textVariables.inactiveBackgroundSelectionColor = inactiveBackgroundSelectionColor;
	}
	
	TextBlock::TextBlock(std::u32string str, TextVariables textVariables, std::vector<BaseLine *> lines) : str(str), BaseTextBlock(textVariables), lines(lines) {
	}
	
	void TextBlock::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) {
		for(BaseCharacter *&character: textCharacters) {
			character->init(renderTarget);
		}
		
		for(BaseLine *&line: lines) {
			line->init(textVariables.size, *textVariables.font, textVariables.TextColor, renderTarget);
		}
	}
	
	std::vector<BaseCharacter *> TextBlock::getCharacters() {
		for(char32_t character: str) {
			textCharacters.push_back(new Character(character, textVariables, lines));
		}
		return textCharacters;
	}
	
	void TextBlock::update() {}
	
	bool TextBlock::updateInteractions(sf::Vector2f mousePosition) {
		return false;
	}
	
	bool TextBlock::in(sf::Vector2f mousePosition) {
		bool result = true;
		for(BaseCharacter *&character: textCharacters) {
			bool buf = character->in(mousePosition);
			if(!buf)
				result = false;
		}
		return result;
	}
	
	TextBlock *TextBlock::copy() {
		std::vector<BaseLine *> copyLines{lines.size()};
		for(int i = 0; i < lines.size(); ++i) {
			copyLines[i] = lines[i];
		}
		return new TextBlock(str, textVariables, copyLines);
	}
	
	TextBlock::~TextBlock() {
		for(BaseLine *&line: lines) {
			delete line;
		}
	}
	
	bool convertPointer(const YAML::Node &node, TextBlock *&textBlock) {
		if (node.IsScalar()) {
			textBlock = new TextBlock{node.as<std::u32string>()};
			return true;
		}

		std::u32string text;
		sf::Color textColor = nullColor;
		sf::Font *font = nullptr;
		sf::Text::Style style = {};
		std::vector<BaseLine *> lines = {};
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
			BaseLine *line;
			node["line"] >> line;
			lines.push_back(line);
		} else if(node["lines"]) {
			for(const YAML::Node &nodeLine: node["lines"]) {
				BaseLine *line;
				nodeLine >> line;
				lines.push_back(line);
			}
		}
		
		{ textBlock = new TextBlock{text, textColor, font, style, lines, size, textSelectionColor, backgroundSelectionColor, inactiveTextSelectionColor, inactiveBackgroundSelectionColor}; return true; }
	}

	template<>
	bool determine<TextBlock>(const YAML::Node &node) {
		return node.IsScalar();
	}
}
