#pragma once

#include "../BaseTextBlock.hpp"
#include "../../BaseCharacter/Character/Character.hpp"
#include "IE/Modules/yaml-cpp/yamlBuilder/determine/determine.hpp"

namespace ie {
	class TextBlock : public BaseTextBlock {
	public:
		TextBlock(std::u32string  text, TextVariables textVariables, std::vector<BoxPtr<BaseLine>>&& lines);
		
		TextBlock(
			std::u32string  text,
			sf::Color textColor = nullColor,
			sf::Font* font = nullptr,
			sf::Text::Style style = {},
			std::vector<BoxPtr<BaseLine>>&& lines = {},
			int size = 0,
			sf::Color textSelectionColor = nullColor,
			sf::Color backgroundSelectionColor = nullColor,
			sf::Color inactiveTextSelectionColor = nullColor,
			sf::Color inactiveBackgroundSelectionColor = nullColor
		);
		
		void setTextVariables(sf::Color TextColor, sf::Color textSelectionColor, sf::Color backgroundSelectionColor, sf::Color inactiveTextSelectionColor, sf::Color inactiveBackgroundSelectionColor, sf::Font* font, uint size) override;
		
		std::vector<BaseCharacter*> getCharacters() override;
		
		void init(InitInfo textInitInfo, InitInfo) override;
		
		bool in(sf::Vector2f mousePosition);
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f) override;
		
		TextBlock* copy() override;
		
	protected:
		std::vector<BoxPtr<BaseCharacter>> textCharacters;
		std::vector<BoxPtr<BaseLine>> lines;
		std::u32string text;
	};
	
	
	template<>
	struct DecodePointer<TextBlock> {
		static bool decodePointer(const YAML::Node& node, TextBlock*& textBlock);
	};
	
	template<>
	bool determine<TextBlock>(const YAML::Node& node);
}