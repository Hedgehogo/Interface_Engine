#pragma once

#include "../BaseTextBlock.hpp"
#include "../../BaseCharacter/Character/Character.hpp"
#include "IE/ieml/shortcuts/shortcuts.hpp"
#include "IE/ieml/ieml-sfml/FileBuffer/FileBuffer.hpp"
#include "IE/utils/utf/to_utf/to_utf.hpp"

namespace ie {
	class TextBlock : public BaseTextBlock {
	public:
		struct Make : public BaseTextBlock::Make {
			sf::String text;
			Indexed<TextStyle> text_stile;
			
			Make(sf::String text, Indexed<TextStyle>&& text_stile);
			
			auto make(TextBockInitInfo init_info) -> BaseTextBlock* override;
		};
		
		TextBlock(Make&& make, TextBockInitInfo init_info);
		
		auto get_characters() -> std::vector<BaseCharacter*> override;
		
		auto set_kerning(char32_t character) -> void override;
		
		auto in(sf::Vector2f point_position) -> bool override;
		
		auto update() -> void override;
		
		auto handle_event(Event) -> bool override;
	
	protected:
		std::vector<BoxPtr<BaseCharacter> > text_characters_;
		std::vector<BoxPtr<BaseLine> > lines_;
		sf::String text_;
		TextStyle const& text_style_;
	};
	
	template<>
	struct Determine<TextBlock::Make> {
		static auto determine(ieml::Node const& node) -> bool;
	};
}

template<>
struct ieml::Decode<char, ie::TextBlock::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::TextBlock::Make>;
};