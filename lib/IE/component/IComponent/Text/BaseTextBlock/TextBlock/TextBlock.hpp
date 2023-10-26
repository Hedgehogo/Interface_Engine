#pragma once

#include "../BaseTextBlock.hpp"
#include "../../BaseCharacter/Character/Character.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/determine/determine.hpp"

namespace ie {
	class TextBlock : public BaseTextBlock {
	public:
		struct Make : public BaseTextBlock::Make {
			std::u32string text;
			orl::Option<sf::Color> text_color = {};
			orl::Option<sf::Font*> font = {};
			orl::Option<sf::Text::Style> style = {};
			std::vector<BoxPtr<BaseLine::Make> > lines = {};
			orl::Option<size_t> size = {};
			orl::Option<sf::Color> text_selection_color = {};
			orl::Option<sf::Color> background_selection_color = {};
			orl::Option<sf::Color> inactive_text_selection_color = {};
			orl::Option<sf::Color> inactive_background_selection_color = {};
			
			Make(
				std::u32string  text,
				const orl::Option<sf::Color>& text_color = {},
				const orl::Option<sf::Font*>& font = {},
				const orl::Option<sf::Text::Style>& style = {},
				std::vector<BoxPtr<BaseLine::Make>>&& lines = {},
				const orl::Option<size_t>& size = {},
				const orl::Option<sf::Color>& text_selection_color = {},
				const orl::Option<sf::Color>& background_selection_color = {},
				const orl::Option<sf::Color>& inactive_text_selection_color = {},
				const orl::Option<sf::Color>& inactive_background_selection_color = {}
			);
			
			BaseTextBlock* make(TextBockInitInfo text_block_init_info) override;
		};
		
		TextBlock(Make&& make, TextBockInitInfo init_info);
		
		TextBlock(std::u32string text, TextVariables text_variables, std::vector<BoxPtr<BaseLine>>&& lines);
		
		TextBlock(
			std::u32string text,
			orl::Option<sf::Color> text_color = {},
			orl::Option<sf::Font*> font = {},
			orl::Option<sf::Text::Style> style = {},
			std::vector<BoxPtr<BaseLine>>&& lines = {},
			orl::Option<size_t> size = {},
			orl::Option<sf::Color> text_selection_color = {},
			orl::Option<sf::Color> background_selection_color = {},
			orl::Option<sf::Color> inactive_text_selection_color = {},
			orl::Option<sf::Color> inactive_background_selection_color = {}
		);
		
		void set_text_variables(
			sf::Color TextColor,
			sf::Color text_selection_color,
			sf::Color background_selection_color,
			sf::Color inactive_text_selection_color,
			sf::Color inactive_background_selection_color,
			sf::Font* font,
			size_t size,
			sf::Text::Style style
		) override;
		
		std::vector<BaseCharacter*> get_characters() override;
		
		void init(TextBockInitInfo text_block_init_info) override;
		
		void set_kerning(char32_t character) override;
		
		bool in(sf::Vector2f mouse_position);
		
		void update() override;
		
		bool update_interactions(sf::Vector2f) override;
		
		TextBlock* copy() override;
	
	protected:
		std::vector<BoxPtr<BaseCharacter>> text_characters;
		std::vector<BoxPtr<BaseLine>> lines;
		std::u32string text;
	};
	
	
	template<>
	struct DecodePointer<TextBlock> {
		static bool decode_pointer(const YAML::Node& node, TextBlock*& text_block);
	};
	
	template<>
	bool determine<TextBlock>(const YAML::Node& node);
}