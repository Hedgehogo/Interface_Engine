#include "Caption.hpp"

#include <algorithm>
#include "IE/ieml/ieml-sfml/FileBuffer/FileBuffer.hpp"
#include "IE/utils/color/hsv_to_rgb/hsv_to_rgb.hpp"
#include "../OnlyDrawable/Capsule/Capsule.hpp"

namespace ie {
	sf::Color Caption::default_color_ = sf::Color::Black;
	int Caption::default_size_ = 10;
	
	void Caption::set_default_color(sf::Color color) {
		default_color_ = color;
	}
	
	void Caption::set_default_size(int size) {
		default_size_ = size;
	}
	
	sf::Color Caption::get_default_color() {
		return default_color_;
	}
	
	int Caption::get_default_size() {
		return default_size_;
	}
	
	Caption::Make::Make(
		sf::String text,
		BoxPtr<INonInteractive::Make>&& background,
		sf::Font& font
	) :
		text(text),
		background(std::move(background)),
		font(font) {
	}
	
	Caption* Caption::Make::make(InitInfo init_info) {
		return new Caption{std::move(*this), init_info};
	}
	
	Caption::Make Caption::Make::set_font_size(int font_size)&& {
		this->font_size = font_size;
		return std::move(*this);
	}
	
	Caption::Make Caption::Make::set_color(sf::Color color)&& {
		this->color = color;
		return std::move(*this);
	}
	
	Caption::Make Caption::Make::set_style(sf::Text::Style style)&& {
		this->style = style;
		return std::move(*this);
	}
	
	Caption::Make Caption::Make::set_positioning(InternalPositioning2::Make positioning)&& {
		this->positioning = positioning;
		return std::move(*this);
	}
	
	Caption::Make Caption::Make::set_cut_back(bool cut_back)&& {
		this->cut_back = cut_back;
		return std::move(*this);
	}
	
	Caption::Make Caption::Make::set_min_size(sf::Vector2f min_size)&& {
		this->min_size = min_size;
		return std::move(*this);
	}
	
	Caption::Caption(Make&& make, InitInfo init_info) :
		OnlyDrawable(init_info),
		cut_back_(make.cut_back),
		str_(make.text),
		background_(make.background->make(init_info.copy(draw_manager_))),
		minimum_size_(make.min_size),
		positioning_(std::move(make.positioning), {init_info.render_target}) {
		this->text_.setString(make.text);
		this->text_.setFont(make.font);
		this->text_.setCharacterSize(make.font_size);
		this->text_.setFillColor(make.color);
		this->text_.setStyle(make.style);
	}
	
	void Caption::set_string(sf::String str) {
		str_ = str;
		text_resize(get_size(), get_position());
	}
	
	void Caption::draw() {
		draw_manager_.draw();
		render_target_->draw(text_);
	}
	
	sf::Vector2f get_text_size(const sf::Text& text) {
		sf::FloatRect local_bounds = text.getLocalBounds();
		
		float count_lines{(static_cast<float>(std::count(text.getString().begin(), text.getString().end(), '\n'))) + 1};
		float character_size{static_cast<float>(text.getFont()->getLineSpacing(text.getCharacterSize()))}; //`getLineSpacing()` returns the actual size of the string
		
		return sf::Vector2f{
			local_bounds.left + local_bounds.width,
			count_lines * text.getLineSpacing() * character_size
		};
	}
	
	void Caption::text_resize(sf::Vector2f size, sf::Vector2f position) {
		sf::Vector2f text_size;
		if(cut_back_) {
			text_.setString(str_);
			text_size = get_text_size(text_);
			sf::String string = this->str_ + sf::String("...");
			while(text_size.x > size.x || text_size.y > size.y) {
				string.erase(string.getSize() - 4, 1);
				text_.setString(string);
				text_size = get_text_size(text_);
			}
		} else {
			text_size = get_text_size(text_);
		}
		
		text_.setPosition(positioning_.find_position(position, size, text_size));
	}
	
	void Caption::resize(sf::Vector2f size, sf::Vector2f position) {
		background_->resize(size, position);
		text_resize(size, position);
	}
	
	sf::Vector2f Caption::get_area_position() const {
		return background_->get_area_position();
	}
	
	sf::Vector2f Caption::get_area_size() const {
		return background_->get_area_size();
	}
	
	sf::Vector2f Caption::get_min_size() const {
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
	
	sf::Vector2f Caption::get_normal_size() const {
		sf::FloatRect rect = text_.getGlobalBounds();
		return max({rect.width, rect.height}, background_->get_normal_size());
	}
	
	void Caption::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		background_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		{
			sf::FloatRect bounds{text_.getGlobalBounds()};
			sf::Vector2f size{bounds.width, bounds.height};
			sf::Vector2f position{bounds.left, bounds.top};
			if(size.x > 0 && size.y > 0) {
				sf::Color color{hsv_to_rgb(static_cast<float>(hue + hue_offset * 2 % 360))};
				
				sf::RectangleShape rectangle{size};
				rectangle.setPosition(position);
				rectangle.setFillColor(sf::Color::Transparent);
				rectangle.setOutlineThickness(1);
				rectangle.setOutlineColor(color);
				
				render_target.draw(rectangle);
				
				sf::CircleShape circle{2, 4};
				circle.setPosition(position + size * 0.5f - sf::Vector2f{2.0f, 2.0f});
				circle.setFillColor(color);
				
				render_target.draw(circle);
			}
		}
		{
			sf::Vector2f size{get_text_size(text_)};
			sf::Vector2f position{get_position()};
			if(size.x > 0 && size.y > 0) {
				sf::Color color{hsv_to_rgb(static_cast<float>(hue + hue_offset % 360))};
				
				sf::RectangleShape rectangle{size};
				rectangle.setPosition(position);
				rectangle.setFillColor(sf::Color::Transparent);
				rectangle.setOutlineThickness(1);
				rectangle.setOutlineColor(color);
				
				render_target.draw(rectangle);
				
				sf::CircleShape circle{2, 4};
				circle.setPosition(position + size * 0.5f - sf::Vector2f{2.0f, 2.0f});
				circle.setFillColor(color);
				
				render_target.draw(circle);
			}
		}
	}
}

orl::Option<ie::Caption::Make> ieml::Decode<char, ie::Caption::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::Caption::Make{
		map.at("text").except().as<sf::String>().except(),
		map.at("background").except().as<ie::BoxPtr<ie::INonInteractive::Make> >().except(),
		map.at("font").except().as<sf::Font&>().except(),
	}
		.set_font_size(map.get_as<int>("font-size").except().ok_or(ie::Caption::get_default_size()))
		.set_color(map.get_as<sf::Color>("color").except().ok_or(ie::Caption::get_default_color()))
		.set_style(map.get_as<ie::LoadTextStyle>("style").except().ok_or({}).style)
		.set_positioning(map.get_as<ie::InternalPositioning2::Make>("positioning").except().ok_or({{0.5, 0.5}}))
		.set_cut_back(map.get_as<bool>("cut-back").except().ok_or(true))
		.set_min_size(map.get_as<sf::Vector2f>("min-size").except().ok_or({}));
}
