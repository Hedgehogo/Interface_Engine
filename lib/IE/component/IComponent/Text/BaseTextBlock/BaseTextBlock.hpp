#pragma once

#include "../BaseCharacter/BaseCharacter.hpp"
#include "../../InitInfo/InitInfo.hpp"
#include "TextBockInitInfo/TextBockInitInfo.hpp"
#include "IE/ieml/Indexed/Indexed.hpp"

namespace ie {
	class BaseTextBlock {
	public:
		struct Make {
			virtual auto make(TextBockInitInfo text_block_init_info) -> BaseTextBlock* = 0;
			
			virtual ~Make() = default;
		};
		
		explicit BaseTextBlock();
		
		virtual auto set_kerning(char32_t character) -> void;
		
		virtual auto in(sf::Vector2f point_position) -> bool = 0;
		
		virtual auto get_characters() -> std::vector<BaseCharacter*> = 0;
		
		virtual auto update() -> void = 0;
		
		virtual auto handle_event(Event event) -> bool = 0;
	
		virtual ~BaseTextBlock() = default;
	};
}
