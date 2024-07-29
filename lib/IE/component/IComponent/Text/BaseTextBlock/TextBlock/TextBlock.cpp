#include "TextBlock.hpp"

#include <utility>

#include "../../BaseLine/Underline/Underline.hpp"
#include "../../BaseLine/StrikeThrough/StrikeThrough.hpp"

namespace ie {
	TextBlock::Make::Make(
		sf::String text,
		Indexed<TextStyle>&& text_stile
	) : text(text),
		text_stile(text_stile) {
	}
	
	auto TextBlock::Make::make(TextBockInitInfo init_info) -> BaseTextBlock* {
		return new TextBlock{std::move(*this), init_info};
	}
	
	auto generate_lines(std::vector<BoxPtr<BaseLine::Make> >&& lines, sf::Text::Style style) -> std::vector<BoxPtr<BaseLine::Make> >&& {
		if(style & sf::Text::Underlined) {
			lines.emplace_back(make_box_ptr<Underline::Make>());
		}
		if(style & sf::Text::StrikeThrough) {
			lines.emplace_back(make_box_ptr<StrikeThrough::Make>());
		}
		return std::move(lines);
	}
	
	TextBlock::TextBlock(Make&& make, TextBockInitInfo init_info) :
		text_(make.text),
		text_style_(make.text_stile.make(init_info.text_style_buffer)) {
		text_characters_.resize(text_.getSize());
		for(auto i{size_t{0}}; i < text_characters_.size(); ++i) {
			text_characters_[i] = make_box_ptr<Character>(text_[i], text_style_, this->lines_, init_info.text_render_target);
		}
	}
	
	auto TextBlock::get_characters() -> std::vector<BaseCharacter*> {
		auto result{std::vector<BaseCharacter*>{text_characters_.size()}};
		for(auto i{size_t{0}}; i < result.size(); ++i) {
			result[i] = text_characters_[i].get();
		}
		return result;
	}
	
	auto TextBlock::update() -> void {
	}
	
	auto TextBlock::handle_event(Event) -> bool {
		return false;
	}
	
	auto TextBlock::in(sf::Vector2f) -> bool {
		return false;
	}
	
	auto TextBlock::set_kerning(char32_t character) -> void {
		for(auto& text_character: text_characters_) {
			text_character->set_kerning(text_style_.font.getKerning(character, text_character->get_char(), text_style_.size));
			character = text_character->get_char();
		}
	}
	
	auto Determine<TextBlock::Make>::determine(ieml::Node const& node) -> bool {
		return node.at("text").is_ok() && node.get("style").is_ok();
	}
}

auto ieml::Decode<char, ie::TextBlock::Make>::decode(ieml::Node const& node) -> orl::Option<ie::TextBlock::Make> {
	auto map{node.get_clear().get_map_view().except()};
	return ie::TextBlock::Make{
		map.at("text").except().as<sf::String>().except(),
		map.at("style").except().as<ie::Indexed<ie::TextStyle> >().except()
	};
}
