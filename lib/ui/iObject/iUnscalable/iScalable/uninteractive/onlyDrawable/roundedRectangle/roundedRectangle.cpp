#include "roundedRectangle.hpp"

namespace ui {
	RoundedRectangle::RoundedRectangle(sf::Color color, float radius) : radius(radius) {
		horizontalRectangle.setFillColor(color);
		verticalRectangle.setFillColor(color);
		circle.setFillColor(color);
		circle.setRadius(radius);
	}
	
	void RoundedRectangle::draw() {
		renderTarget->draw(horizontalRectangle);
		renderTarget->draw(verticalRectangle);
		circle.setPosition(position);
		renderTarget->draw(circle);
		circle.setPosition(position.x + size.x - radius * 2, position.y);
		renderTarget->draw(circle);
		circle.setPosition(position.x, position.y + size.y - radius * 2);
		renderTarget->draw(circle);
		circle.setPosition(position.x + size.x - radius * 2, position.y + size.y - radius * 2);
		renderTarget->draw(circle);
	}
	
	void RoundedRectangle::resize(sf::Vector2f size, sf::Vector2f position) {
		Layout::resize(size, position);
		verticalRectangle.setSize({size.x - radius * 2, size.y});
		verticalRectangle.setPosition(position + sf::Vector2f{radius, 0});
		horizontalRectangle.setSize({size.x, size.y - radius * 2});
		horizontalRectangle.setPosition(position + sf::Vector2f{0, radius});
	}
	
	sf::Vector2f RoundedRectangle::getMinSize() {
		return sf::Vector2f(radius * 2, radius * 2);
	}
	
	sf::Vector2f RoundedRectangle::getNormalSize() {
		return sf::Vector2f(radius * 2, radius * 2);
	}
	
	RoundedRectangle *RoundedRectangle::copy() {
		RoundedRectangle *rectangle{new RoundedRectangle{circle.getFillColor(), radius}};
		OnlyDrawable::copy(rectangle);
		Layout::copy(rectangle);
		rectangle->resize(size, position);
		return rectangle;
	}
	
	RoundedRectangle *RoundedRectangle::createFromYaml(const YAML::Node &node) {
		sf::Color color;
		float radius{};
		node["color"] >> color;
		node["radius"] >> radius;
		return new RoundedRectangle{color, radius};
	}
}
