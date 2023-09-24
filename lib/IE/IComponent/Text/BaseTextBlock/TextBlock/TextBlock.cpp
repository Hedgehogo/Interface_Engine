#include "TextBlock.hpp"

#include <utility>

#include "../../BaseLine/Underline/Underline.hpp"
#include "../../BaseLine/StrikeThrough/StrikeThrough.hpp"
#include "IE/Modules/yaml-cpp/fileBuffer/fileBuffer.hpp"

namespace ie {
	TextBlock::Make::Make(
		std::u32string text,
		const orl::Option<sf::Color>& textColor,
		const orl::Option<sf::Font*>& font,
		const orl::Option<sf::Text::Style>& style,
		std::vector<BoxPtr<BaseLine::Make>>&& lines,
		const orl::Option<uint>& size,
		const orl::Option<sf::Color>& textSelectionColor,
		const orl::Option<sf::Color>& backgroundSelectionColor,
		const orl::Option<sf::Color>& inactiveTextSelectionColor,
		const orl::Option<sf::Color>& inactiveBackgroundSelectionColor
	) : text(std::move(text)),
		textColor(textColor),
		font(font),
		style(style),
		lines(std::move(lines)),
		size(size),
		textSelectionColor(textSelectionColor),
		backgroundSelectionColor(backgroundSelectionColor),
		inactiveTextSelectionColor(inactiveTextSelectionColor),
		inactiveBackgroundSelectionColor(inactiveBackgroundSelectionColor) {
	}
	
	BaseTextBlock* TextBlock::Make::make(TextBockInitInfo textBlockInitInfo) {
		return new TextBlock{std::move(*this), textBlockInitInfo};
	}
	
	std::vector<BoxPtr<BaseLine>>&& generateLines(std::vector<BoxPtr<BaseLine>>&& lines, sf::Text::Style style) {
		if(style & sf::Text::Underlined)
			lines.emplace_back(makeBoxPtr<Underline>());
		if(style & sf::Text::StrikeThrough)
			lines.emplace_back(makeBoxPtr<StrikeThrough>());
		return std::move(lines);
	}
	
	TextBlock::TextBlock(Make&& make, TextBockInitInfo initInfo) :
		BaseTextBlock(
			{
				make.textColor.some_or(initInfo.textVariables.textColor.some()),
				make.textSelectionColor.some_or(initInfo.textVariables.textSelectionColor.some()),
				make.backgroundSelectionColor.some_or(initInfo.textVariables.backgroundSelectionColor.some()),
				make.inactiveTextSelectionColor.some_or(initInfo.textVariables.inactiveTextSelectionColor.some()),
				make.inactiveBackgroundSelectionColor.some_or(initInfo.textVariables.inactiveBackgroundSelectionColor.some()),
				make.font.some_or(initInfo.textVariables.font.some()),
				make.style.some_or(initInfo.textVariables.style.some()),
				make.size.some_or(initInfo.textVariables.size.some()),
			}
		),
		lines(
			generateLines(
				mapMake(
					std::move(make.lines),
					LineInitInfo{
						textVariables.size.some(),
						*textVariables.font.some(),
						textVariables.textColor.some(),
						initInfo.textRenderTarget
					}
				),
				textVariables.style.some()
			)
		),
		text(std::move(make.text)) {
		textCharacters.resize(text.size());
		for(std::size_t i = 0; i < textCharacters.size(); ++i) {
			textCharacters[i] = makeBoxPtr<Character>(text[i], textVariables, this->lines);
		}
		
		for(auto& character: textCharacters) {
			character->init(initInfo.textRenderTarget);
		}
	}
	
	TextBlock::TextBlock(
		std::u32string text,
		orl::Option<sf::Color> textColor,
		orl::Option<sf::Font*> font,
		orl::Option<sf::Text::Style> style,
		std::vector<BoxPtr<BaseLine>>&& lines,
		orl::Option<uint> size,
		orl::Option<sf::Color> textSelectionColor,
		orl::Option<sf::Color> backgroundSelectionColor,
		orl::Option<sf::Color> inactiveTextSelectionColor,
		orl::Option<sf::Color> inactiveBackgroundSelectionColor
	) :
		lines(style ? generateLines(std::move(lines), style.some()) : std::move(lines)), text(std::move(text)) {
		textVariables.textColor = textColor;
		textVariables.font = font;
		textVariables.style = style;
		textVariables.size = size;
		textVariables.textSelectionColor = textSelectionColor;
		textVariables.backgroundSelectionColor = backgroundSelectionColor;
		textVariables.inactiveTextSelectionColor = inactiveTextSelectionColor;
		textVariables.inactiveBackgroundSelectionColor = inactiveBackgroundSelectionColor;
	}
	
	TextBlock::TextBlock(std::u32string text, TextVariables textVariables, std::vector<BoxPtr<BaseLine>>&& lines) :
		BaseTextBlock(textVariables), lines(std::move(lines)), text(std::move(text)) {
	}
	
	void TextBlock::init(TextBockInitInfo textBlockInitInfo) {
		for(auto& character: textCharacters) {
			character->init(textBlockInitInfo.renderTarget);
		}
		
		for(auto& line: lines) {
			line->init(
				{
					textVariables.size.some(),
					*textVariables.font.some(),
					textVariables.textColor.some(),
					textBlockInitInfo.renderTarget
				}
			);
		}
	}
	
	void TextBlock::setTextVariables(
		sf::Color TextColor,
		sf::Color textSelectionColor,
		sf::Color backgroundSelectionColor,
		sf::Color inactiveTextSelectionColor,
		sf::Color inactiveBackgroundSelectionColor,
		sf::Font* font,
		uint size,
		sf::Text::Style style
	) {
		BaseTextBlock::setTextVariables(
			TextColor,
			textSelectionColor,
			backgroundSelectionColor,
			inactiveTextSelectionColor,
			inactiveBackgroundSelectionColor,
			font,
			size,
			style
		);
		
		textCharacters.resize(text.size());
		for(std::size_t i = 0; i < textCharacters.size(); ++i) {
			textCharacters[i] = makeBoxPtr<Character>(text[i], textVariables, this->lines);
		}
	}
	
	std::vector<BaseCharacter*> TextBlock::getCharacters() {
		std::vector<BaseCharacter*> result{textCharacters.size()};
		for(size_t i = 0; i < result.size(); ++i) {
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
		} else {
			textBlock = new TextBlock{
				node["text"].as<std::u32string>(),
				convDef<orl::Option<sf::Color> >(node["text-color"], {}),
				convDef<orl::Option<sf::Font*> >(node["font"], {}),
				convDef<orl::Option<sf::Text::Style> >(node["style"], {}),
				node["line"] ? makeVector(node["line"].as<BoxPtr<BaseLine > >()) : node["line"].as<std::vector<BoxPtr<BaseLine> > >(),
				convDef<orl::Option<uint> >(node["size"], {}),
				convDef<orl::Option<sf::Color> >(node["text-selection-color"], {}),
				convDef<orl::Option<sf::Color> >(node["background-selection-color"], {}),
				convDef<orl::Option<sf::Color> >(node["inactive-text-selection-color"], {}),
				convDef<orl::Option<sf::Color> >(node["inactive-background-selection-color"], {})
			};
		}
		return true;
	}
	
	template<>
	bool determine<TextBlock>(const YAML::Node& node) {
		return node.IsScalar();
	}
}
