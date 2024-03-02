#pragma once

#include "../BaseTextBlock.hpp"
#include "../../BaseCharacter/Character/Character.hpp"
#include "IE/modules/yaml-cpp/yaml.hpp"
#include "IE/ieml/shortcuts/shortcuts.hpp"
#include "IE/ieml/ieml-sfml/FileBuffer/FileBuffer.hpp"
#include "IE/utils/utf/to_utf/to_utf.hpp"

namespace ie {
	class TextBlock : public BaseTextBlock {
	public:
		struct Make : public BaseTextBlock::Make {
			sf::String text;
			orl::Option<sf::Color> text_color = {};
			orl::Option<sf::Font&> font = {};
			orl::Option<sf::Text::Style> style = {};
			std::vector<BoxPtr<BaseLine::Make> > lines = {};
			orl::Option<size_t> size = {};
			orl::Option<sf::Color> text_selection_color = {};
			orl::Option<sf::Color> background_selection_color = {};
			orl::Option<sf::Color> inactive_text_selection_color = {};
			orl::Option<sf::Color> inactive_background_selection_color = {};
			
			Make(
				sf::String  text,
				orl::Option<sf::Color> text_color = {},
				orl::Option<sf::Font&> font = {},
				orl::Option<sf::Text::Style> style = {},
				std::vector<BoxPtr<BaseLine::Make> >&& lines = {},
				orl::Option<size_t> size = {},
				orl::Option<sf::Color> text_selection_color = {},
				orl::Option<sf::Color> background_selection_color = {},
				orl::Option<sf::Color> inactive_text_selection_color = {},
				orl::Option<sf::Color> inactive_background_selection_color = {}
			);
			
			auto make(TextBockInitInfo init_info) -> BaseTextBlock* override;
		};
		
		TextBlock(Make&& make, TextBockInitInfo init_info);
		
		void set_text_variables(
			sf::Color text_color,
			sf::Color text_selection_color,
			sf::Color background_selection_color,
			sf::Color inactive_text_selection_color,
			sf::Color inactive_background_selection_color,
			sf::Font& font,
			size_t size,
			sf::Text::Style style
		) override;
		
		auto get_characters() -> std::vector<BaseCharacter*> override;
		
		auto set_kerning(char32_t character) -> void override;
		
		auto in(sf::Vector2f mouse_position) -> bool override;
		
		auto update() -> void override;
		
		auto update_interactions(sf::Vector2f) -> bool override;
	
	protected:
		std::vector<BoxPtr<BaseCharacter> > text_characters_;
		std::vector<BoxPtr<BaseLine> > lines_;
		sf::String text_;
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