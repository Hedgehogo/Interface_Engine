#include <algorithm>
#include "IE/ieml/ieml-sfml/FileBuffer/FileBuffer.hpp"
#include "IE/utils/color/hsv_to_rgb/hsv_to_rgb.hpp"
#include "../OnlyDrawable/Capsule/Capsule.hpp"

namespace ie {
	namespace make_system {
		template<typename StringStorage_>
		BasicCaption<StringStorage_>::BasicCaption(
			typename CaptionString<StringStorage_>::Make text,
			BoxPtr<INonInteractive::Make>&& background,
			sf::Font& font
		) :
			text(std::move(text)),
			background(std::move(background)),
			font(font) {
		}
		
		template<typename StringStorage_>
		auto BasicCaption<StringStorage_>::set_font_size(int font_size)&& -> BasicCaption {
			this->font_size = font_size;
			return std::move(*this);
		}
		
		template<typename StringStorage_>
		auto BasicCaption<StringStorage_>::set_color(sf::Color color)&& -> BasicCaption {
			this->color = color;
			return std::move(*this);
		}
		
		template<typename StringStorage_>
		auto BasicCaption<StringStorage_>::set_style(sf::Text::Style style)&& -> BasicCaption {
			this->style = style;
			return std::move(*this);
		}
		
		template<typename StringStorage_>
		auto BasicCaption<StringStorage_>::set_positioning(InternalPositioning2::Make positioning)&& -> BasicCaption {
			this->positioning = positioning;
			return std::move(*this);
		}
		
		template<typename StringStorage_>
		auto BasicCaption<StringStorage_>::set_cut_back(bool cut_back)&& -> BasicCaption {
			this->cut_back = cut_back;
			return std::move(*this);
		}
		
		template<typename StringStorage_>
		auto BasicCaption<StringStorage_>::set_min_size(sf::Vector2f min_size)&& -> BasicCaption {
			this->min_size = min_size;
			return std::move(*this);
		}
		
		template<typename StringStorage_>
		auto BasicCaption<StringStorage_>::make(InitInfo init_info) -> ie::BasicCaption<StringStorage_>* {
			return new ie::BasicCaption<StringStorage_>{std::move(*this), init_info};
		}
	}
	
	template<typename StringStorage_>
	sf::Color BasicCaption<StringStorage_>::default_color_ = sf::Color::Black;
	
	template<typename StringStorage_>
	int BasicCaption<StringStorage_>::default_size_ = 10;
	
	template<typename StringStorage_>
	auto BasicCaption<StringStorage_>::set_default_color(sf::Color color) -> void {
		default_color_ = color;
	}
	
	template<typename StringStorage_>
	auto BasicCaption<StringStorage_>::set_default_size(int size) -> void {
		default_size_ = size;
	}
	
	template<typename StringStorage_>
	auto BasicCaption<StringStorage_>::get_default_color() -> sf::Color {
		return default_color_;
	}
	
	template<typename StringStorage_>
	auto BasicCaption<StringStorage_>::get_default_size() -> int {
		return default_size_;
	}
	
	template<typename StringStorage_>
	BasicCaption<StringStorage_>::BasicCaption(Make&& make, InitInfo init_info) :
		OnlyDrawable(init_info),
		cut_back_(make.cut_back),
		str_(CaptionString<StringStorage_>::make(*this, std::move(make.text), init_info)),
		background_(make.background->make(init_info.copy(draw_manager_))),
		minimum_size_(make.min_size),
		positioning_(std::move(make.positioning), {init_info.render_target}) {
		text_.setString(CaptionString<StringStorage_>::get(str_));
		text_.setFont(make.font);
		text_.setCharacterSize(make.font_size);
		text_.setFillColor(make.color);
		text_.setStyle(make.style);
	}
	
	template<typename StringStorage_>
	auto BasicCaption<StringStorage_>::set_string(sf::String str) -> void {
		CaptionString<StringStorage_>::set(str_, str);
		text_resize(get_size(), get_position());
	}
	
	template<typename StringStorage_>
	auto BasicCaption<StringStorage_>::draw() -> void {
		draw_manager_.draw();
		render_target_->draw(text_);
	}
	
	template<typename StringStorage_>
	auto BasicCaption<StringStorage_>::get_text_size(sf::Text const& text) -> sf::Vector2f {
		auto local_bounds{text.getLocalBounds()};
		
		auto count_lines{(static_cast<float>(std::count(text.getString().begin(), text.getString().end(), '\n'))) + 1};
		//`getLineSpacing()` returns the actual size of the string
		auto character_size{static_cast<float>(text.getFont()->getLineSpacing(text.getCharacterSize()))};
		
		return {local_bounds.left + local_bounds.width, count_lines * text.getLineSpacing() * character_size};
	}
	
	template<typename StringStorage_>
	auto BasicCaption<StringStorage_>::text_resize(sf::Vector2f size, sf::Vector2f position) -> void {
		sf::Vector2f text_size;
		if(cut_back_) {
			auto string{CaptionString<StringStorage_>::get(str_)};
			text_.setString(string);
			text_size = get_text_size(text_);
			if(text_size.x > size.x || text_size.y > size.y) {
				string = string + sf::String("...");
				while(text_size.x > size.x || text_size.y > size.y) {
					string.erase(string.getSize() - 4, 1);
					text_.setString(string);
					text_size = get_text_size(text_);
				}
			}
		} else {
			text_size = get_text_size(text_);
		}
		
		text_.setPosition(positioning_.find_position(position, size, text_size));
	}
	
	template<typename StringStorage_>
	auto BasicCaption<StringStorage_>::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		background_->resize(size, position);
		text_resize(size, position);
	}
	
	template<typename StringStorage_>
	auto BasicCaption<StringStorage_>::get_area_position() const -> sf::Vector2f {
		return background_->get_area_position();
	}
	
	template<typename StringStorage_>
	auto BasicCaption<StringStorage_>::get_area_size() const -> sf::Vector2f {
		return background_->get_area_size();
	}
	
	template<typename StringStorage_>
	auto BasicCaption<StringStorage_>::get_min_size() const -> sf::Vector2f {
		return max(
			max(
				minimum_size_,
				get_text_size([&] {
					if(cut_back_) {
						return sf::Text{"...", *text_.getFont(), text_.getCharacterSize()};
					} else {
						return text_;
					}
				}())
			),
			background_->get_min_size()
		);
	}
	
	template<typename StringStorage_>
	auto BasicCaption<StringStorage_>::get_normal_size() const -> sf::Vector2f {
		auto rect{text_.getGlobalBounds()};
		return max({rect.width, rect.height}, background_->get_normal_size());
	}
	
	template<typename StringStorage_>
	auto BasicCaption<StringStorage_>::draw_debug(
		sf::RenderTarget& render_target,
		int indent,
		int indent_addition,
		size_t hue,
		size_t hue_offset
	) -> void {
		background_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		auto draw_rectangle = [&](sf::Vector2f size, sf::Vector2f position) {
			if(size.x > 0 && size.y > 0) {
				auto color{hsv_to_rgb(static_cast<float>(hue + hue_offset * 2 % 360))};
				
				auto rectangle{sf::RectangleShape{size}};
				rectangle.setPosition(position);
				rectangle.setFillColor(sf::Color::Transparent);
				rectangle.setOutlineThickness(1);
				rectangle.setOutlineColor(color);
				
				render_target.draw(rectangle);
				
				auto circle{sf::CircleShape{2, 4}};
				circle.setPosition(position + size * 0.5f - sf::Vector2f{2.0f, 2.0f});
				circle.setFillColor(color);
				
				render_target.draw(circle);
			}
		};
		auto bounds{text_.getGlobalBounds()};
		draw_rectangle({bounds.width, bounds.height}, {bounds.left, bounds.top});
		draw_rectangle(get_text_size(text_), get_position());
	}
}

template<typename StringStorage_>
auto ieml::Decode<char, ie::make_system::BasicCaption<StringStorage_> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::make_system::BasicCaption<StringStorage_> > {
	auto map{node.get_map_view().except()};
	return ie::make_system::BasicCaption<StringStorage_>{
		map.at("text").except().as<typename ie::CaptionString<StringStorage_>::Make>().except(),
		map.at("background").except().as<ie::BoxPtr<ie::INonInteractive::Make> >().except(),
		map.at("font").except().as<sf::Font&>().except(),
	}
		.set_font_size(map.get_as<int>("font-size").except().ok_or(ie::BasicCaption<StringStorage_>::get_default_size()))
		.set_color(map.get_as<sf::Color>("color").except().ok_or(ie::BasicCaption<StringStorage_>::get_default_color()))
		.set_style(map.get_as<ie::LoadTextStyle>("style").except().ok_or({}).style)
		.set_positioning(map.get_as<ie::InternalPositioning2::Make>("positioning").except().ok_or({{0.5, 0.5}}))
		.set_cut_back(map.get_as<bool>("cut-back").except().ok_or(true))
		.set_min_size(map.get_as<sf::Vector2f>("min-size").except().ok_or({}));
}
