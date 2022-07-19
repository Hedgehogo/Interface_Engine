#include "roundedRectangle.h"

ui::RoundedRectangle::RoundedRectangle(sf::Color color, float radius) : radius(radius) {
	horizontalRectangle.setFillColor(color);
	verticalRectangle.setFillColor(color);
	circle.setFillColor(color);
	circle.setRadius(radius);
}

void ui::RoundedRectangle::draw() {
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

void ui::RoundedRectangle::resize(sf::Vector2f size, sf::Vector2f position) {
	Layout::resize(size, position);
	verticalRectangle.setSize({size.x - radius * 2, size.y});
	verticalRectangle.setPosition(position + sf::Vector2f{radius, 0});
	horizontalRectangle.setSize({size.x, size.y - radius * 2});
	horizontalRectangle.setPosition(position + sf::Vector2f{0, radius});
}

sf::Vector2f ui::RoundedRectangle::getMinSize() {
	return sf::Vector2f(radius * 2, radius * 2);
}

sf::Vector2f ui::RoundedRectangle::getNormalSize() {
	return sf::Vector2f(radius * 2, radius * 2);
}

ui::RoundedRectangle *ui::RoundedRectangle::copy() {
	RoundedRectangle* rectangle{new RoundedRectangle{circle.getFillColor(), radius}};
	IDrawable::copy(rectangle);
	Layout::copy(rectangle);
	rectangle->resize(size, position);
	return rectangle;
}
