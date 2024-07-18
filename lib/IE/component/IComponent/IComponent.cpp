#include "IComponent.hpp"
#include "IE/utils/color/hsv_to_rgb/hsv_to_rgb.hpp"

namespace ie {
	auto IComponent::set_position(sf::Vector2f position) -> void {
		resize(get_area_size(), position);
	}
	
	auto IComponent::move(sf::Vector2f offset) -> void {
		resize(get_area_size(), get_area_position() + offset);
	}
	
	auto IComponent::set_size(sf::Vector2f size) -> void {
		resize(size, get_area_position());
	}
	
	auto IComponent::get_position() const -> sf::Vector2f {
		return get_area_position();
	}
	
	auto IComponent::get_size() const -> sf::Vector2f {
		return get_area_size();
	}
	
	auto IComponent::in_area(sf::Vector2f point_position) const -> bool {
		auto size{get_area_size()};
		auto position{get_area_position()};
		return
			point_position.x > position.x && point_position.x < position.x + size.x &&
			point_position.y > position.y && point_position.y < position.y + size.y;
	}
	
	auto IComponent::in(sf::Vector2f point_position) const -> bool {
		return in_area(point_position);
	}
	
	auto IComponent::draw_debug(sf::Vector2f position, sf::Vector2f size, sf::RenderTarget& render_target, size_t hue) -> void {
		if(size.x > 0 && size.y > 0) {
			auto color{hsv_to_rgb(static_cast<float>(hue % 360))};
			
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
	}
	
	auto IComponent::draw_debug(sf::RenderTarget& render_target, int indent, int, size_t hue, size_t) -> void {
		auto size{this->get_area_size() - static_cast<sf::Vector2f>(sf::Vector2i{indent * 2 + 2, indent * 2 + 2})};
		auto position{this->get_area_position() + static_cast<sf::Vector2f>(sf::Vector2i{indent + 1, indent + 1})};
		if(size.x > 0 && size.y > 0) {
			auto color{hsv_to_rgb(static_cast<float>(hue % 360))};
			
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
	}
}