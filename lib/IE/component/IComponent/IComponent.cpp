#include "IComponent.hpp"
#include "IE/utils/color/hsv_to_rgb/hsv_to_rgb.hpp"

namespace ie {
	void IComponent::set_position(sf::Vector2f position) {
		resize(get_area_size(), position);
	}
	
	void IComponent::move(sf::Vector2f position) {
		resize(get_area_size(), get_area_position() + position);
	}
	
	void IComponent::set_size(sf::Vector2f size) {
		resize(size, get_area_position());
	}
	
	sf::Vector2f IComponent::get_position() const {
		return get_area_position();
	}
	
	sf::Vector2f IComponent::get_size() const {
		return get_area_size();
	}
	
	bool IComponent::in_area(sf::Vector2f point_position) {
		sf::Vector2f size{get_area_size()};
		sf::Vector2f position{get_area_position()};
		return point_position.x > position.x && point_position.x < position.x + size.x &&
			   point_position.y > position.y && point_position.y < position.y + size.y;
	}
	
	bool IComponent::in(sf::Vector2f point_position) {
		return in_area(point_position);
	}
	
	void IComponent::draw_debug(sf::Vector2f position, sf::Vector2f size, sf::RenderTarget& render_target, size_t hue) {
		if(size.x > 0 && size.y > 0) {
			sf::Color color{hsv_to_rgb(static_cast<float>(hue % 360))};
			
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
	
	void IComponent::draw_debug(sf::RenderTarget& render_target, int indent, int, size_t hue, size_t) {
		sf::Vector2f size{this->get_area_size() - static_cast<sf::Vector2f>(sf::Vector2i{indent * 2 + 2, indent * 2 + 2})};
		sf::Vector2f position{this->get_area_position() + static_cast<sf::Vector2f>(sf::Vector2i{indent + 1, indent + 1})};
		if(size.x > 0 && size.y > 0) {
			sf::Color color{hsv_to_rgb(static_cast<float>(hue % 360))};
			
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