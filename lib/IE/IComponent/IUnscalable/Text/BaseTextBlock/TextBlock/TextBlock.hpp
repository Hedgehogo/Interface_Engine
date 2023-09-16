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
			orl::Option<sf::Color> textColor = {},
			orl::Option<sf::Font*> font = nullptr,
			orl::Option<sf::Text::Style> style = {},
			std::vector<BoxPtr<BaseLine>>&& lines = {},
			orl::Option<uint> size = {},
			orl::Option<sf::Color> textSelectionColor = {},
			orl::Option<sf::Color> backgroundSelectionColor = {},
			orl::Option<sf::Color> inactiveTextSelectionColor = {},
			orl::Option<sf::Color> inactiveBackgroundSelectionColor = {}
		);
		
		void setTextVariables(sf::Color TextColor, sf::Color textSelectionColor, sf::Color backgroundSelectionColor, sf::Color inactiveTextSelectionColor, sf::Color inactiveBackgroundSelectionColor, sf::Font* font, uint size,
							  sf::Text::Style style) override;
		
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