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
			virtual BaseTextBlock* make(TextBockInitInfo text_block_init_info) = 0;
			
			virtual ~Make() = default;
		};
		
		BaseTextBlock();
		
		BaseTextBlock(TextVariables text_variables);
		
		virtual void set_text_variables(
			sf::Color TextColor,
			sf::Color text_selection_color,
			sf::Color background_selection_color,
			sf::Color inactive_text_selection_color,
			sf::Color inactive_background_selection_color,
			sf::Font* font,
			size_t size,
			sf::Text::Style style
		);
		
		virtual void init(TextBockInitInfo text_block_init_info) = 0;
		
		virtual void set_kerning(char32_t character);
		
		virtual bool in(sf::Vector2f mouse_position) = 0;
		
		virtual std::vector<BaseCharacter*> get_characters() = 0;
		
		virtual void update() = 0;
		
		virtual bool update_interactions(sf::Vector2f mouse_position) = 0;
		
		virtual BaseTextBlock* copy() = 0;
	
		virtual ~BaseTextBlock() = default;
		
	protected:
		TextVariables text_variables;
	};
}
