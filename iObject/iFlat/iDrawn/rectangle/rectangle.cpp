#include "rectangle.h"

ui::Rectangle::Rectangle(sf::Color color, float radius) : radius(radius) {
	horizontalRectangle.setFillColor(color);
	verticalRectangle.setFillColor(color);
	circle.setFillColor(color);
	circle.setRadius(radius);
}

void ui::Rectangle::draw() {
	window->draw(horizontalRectangle);
	window->draw(verticalRectangle);
	circle.setPosition(position);
	window->draw(circle);
	circle.setPosition(position.x + size.x - radius * 2, position.y);
	window->draw(circle);
	circle.setPosition(position.x, position.y + size.y - radius * 2);
	window->draw(circle);
	circle.setPosition(position.x + size.x - radius * 2, position.y + size.y - radius * 2);
	window->draw(circle);
}

void ui::Rectangle::resize(sf::Vector2f size, sf::Vector2f position) {
	this->size = size;
	this->position = position;
	verticalRectangle.setSize({size.x - radius * 2, size.y});
	verticalRectangle.setPosition(position + sf::Vector2f{radius, 0});
	horizontalRectangle.setSize({size.x, size.y - radius * 2});
	horizontalRectangle.setPosition(position + sf::Vector2f{0, radius});
}

sf::Vector2f ui::Rectangle::getMinSize() {
	return sf::Vector2f(radius * 2, radius * 2);
}

sf::Vector2f ui::Rectangle::getNormalSize() {
	return sf::Vector2f(radius * 2, radius * 2);
}

ui::Rectangle *ui::Rectangle::copy() {
	Rectangle* rectangle{new Rectangle{circle.getFillColor(), radius}};
	IDrawn::copy(rectangle);
	rectangle->resize(size, position);
	return rectangle;
}
