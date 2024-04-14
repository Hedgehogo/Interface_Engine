#pragma once

#include "../TextVariables/TextVariables.hpp"
#include "../BaseCharacter/BaseCharacter.hpp"
#include "../../IScalable/BasicInteractiveData/BasicInteractiveData.hpp"
#include "../../InitInfo/InitInfo.hpp"
#include "TextBockInitInfo/TextBockInitInfo.hpp"

namespace ie {
	class BaseTextBlock {
	public:
		struct Make {
			virtual auto make(TextBockInitInfo text_block_init_info) -> BaseTextBlock* = 0;
			
			virtual ~Make() = default;
		};
		
		explicit BaseTextBlock(TextVariables text_variables);
		
		virtual void set_text_variables(
			sf::Color text_color,
			sf::Color text_selection_color,
			sf::Color background_selection_color,
			sf::Color inactive_text_selection_color,
			sf::Color inactive_background_selection_color,
			sf::Font& font,
			size_t size,
			sf::Text::Style style
		);
		
		virtual auto set_kerning(char32_t character) -> void;
		
		virtual auto in(sf::Vector2f point_position) -> bool = 0;
		
		virtual auto get_characters() -> std::vector<BaseCharacter*> = 0;
		
		virtual auto update() -> void = 0;
		
		virtual auto update_interactions(Event event) -> bool = 0;
	
		virtual ~BaseTextBlock() = default;
		
	protected:
		TextVariables text_variables_;
	};
}
