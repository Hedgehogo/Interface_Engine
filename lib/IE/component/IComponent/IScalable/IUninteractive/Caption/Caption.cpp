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
		BoxPtr<IUninteractive::Make>&& background,
		sf::Font& font,
		sf::Vector2f min_size,
		int font_size,
		sf::Color color,
		sf::Text::Style style,
		float rotation,
		InternalPositioning2::Make positioning,
		bool cut_back
	) :
		text(text),
		background(std::move(background)),
		font(font),
		font_size(font_size),
		color(color),
		style(style),
		rotation(rotation),
		positioning(positioning),
		cut_back(cut_back),
		min_size(min_size) {
	}
	
	Caption::Make::Make(
		sf::String text,
		BoxPtr<IUninteractive::Make>&& background,
		sf::Font& font,
		int font_size,
		sf::Color color,
		sf::Text::Style style,
		float rotation,
		InternalPositioning2::Make positioning,
		bool cut_back
	) :
		text(text),
		background(std::move(background)),
		font(font),
		font_size(font_size),
		color(color),
		style(style),
		rotation(rotation),
		positioning(positioning),
		cut_back(cut_back) {
	}
	
	Caption* Caption::Make::make(InitInfo init_info) {
		return new Caption{std::move(*this), init_info};
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
		this->text_.setRotation(make.rotation);
	}
	
	void Caption::draw() {
		draw_manager_.draw();
		render_target_->draw(text_);
	}
	
	sf::FloatRect Caption::get_bounds(const sf::Text& text) const {
		sf::FloatRect local_bounds = text.getLocalBounds();
		
		float count_enter{(static_cast<float>(std::count(text.getString().begin(), text.getString().end(), '\n')))};
		float character_size{static_cast<float>(text.getFont()->getLineSpacing(text.getCharacterSize()))};
		
		sf::FloatRect bounds{
			{0, 0},
			{
			 local_bounds.left + local_bounds.width,
				text.getCharacterSize() + (count_enter * text.getLineSpacing() * character_size)
			}
		};
		return text.getTransform().transformRect(bounds);
	}
	
	void Caption::resize(sf::Vector2f size, sf::Vector2f position) {
		background_->resize(size, position);
		text_.setString(str_);
		
		sf::FloatRect bounds = get_bounds(text_);
		if(cut_back_) {
			sf::String string = this->str_ + sf::String("...");
			while(bounds.width > size.x || bounds.height > size.y) {
				string.erase(string.getSize() - 4, 1);
				text_.setString(string);
				bounds = get_bounds(text_);
			}
		}
		sf::Vector2f find_position{positioning_.find_position(position, size, {bounds.width, bounds.height})};
		text_.setPosition(find_position - sf::Vector2f(get_bounds(text_).left - text_.getPosition().x, get_bounds(text_).top - text_.getPosition().y));
	}
	
	sf::Vector2f Caption::get_area_position() const {
		return background_->get_area_position();
	}
	
	sf::Vector2f Caption::get_area_size() const {
		return background_->get_area_size();
	}
	
	sf::Vector2f Caption::get_min_size() const {
		sf::FloatRect bounds{get_bounds(sf::Text{"...", *text_.getFont(), text_.getCharacterSize()})};
		return max(
			max(
				minimum_size_,
				(cut_back_ ?
				 sf::Vector2f{bounds.width, bounds.height} :
				 sf::Vector2f{})
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
			sf::FloatRect bounds{get_bounds(text_)};
			sf::Vector2f size{bounds.width, bounds.height};
			sf::Vector2f position{bounds.left, bounds.top};
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
		map.at("text").except().as<sf::String>().move_except(),
		map.at("background").except().as<ie::BoxPtr<ie::IUninteractive::Make> >().move_except(),
		map.at("background").except().as<sf::Font&>().except(),
		map.get_as<sf::Vector2f>("min-size").ok_or({}),
		map.get_as<int>("font-size").ok_or(ie::Caption::get_default_size()),
		map.get_as<sf::Color>("color").ok_or(ie::Caption::get_default_color()),
		map.get_as<ie::LoadTextStyle>("style").ok_or({}).style,
		map.get_as<float>("rotation").ok_or(0.0),
		ie::InternalPositioning2::Make{{0.5, 0.5}},
		map.get_as<bool>("cut-back").ok_or(true)
	};
}
