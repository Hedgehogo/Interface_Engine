#include "capsule.h"

ui::Capsule::Capsule(sf::Color color) : Layout() {
	rectangle.setFillColor(color);
	circle.setFillColor(color);
}

void ui::Capsule::draw() {
	renderTarget->draw(rectangle);
	circle.setPosition(position);
	renderTarget->draw(circle);
	if(size.x > size.y) {
		circle.setPosition({position.x + size.x - size.y, position.y});
	} else {
		circle.setPosition({position.x, position.y + size.y - size.x});
	}
	renderTarget->draw(circle);
}

void ui::Capsule::resize(sf::Vector2f size, sf::Vector2f position) {
	Layout::resize(size, position);
	if(size.x > size.y) {
		rectangle.setSize({size.x - size.y, size.y});
		rectangle.setPosition(position + sf::Vector2f{size.y / 2, 0});
		circle.setRadius(size.y / 2);
	} else {
		rectangle.setSize({size.x, size.y - size.x});
		rectangle.setPosition(position + sf::Vector2f{0, size.x / 2});
		circle.setRadius(size.x / 2);
	}
}

sf::Vector2f ui::Capsule::getMinSize() {
	return {0, 0};
}

sf::Vector2f ui::Capsule::getNormalSize() {
	return {1, 1};
}

ui::Capsule *ui::Capsule::copy() {
	Capsule* capsule{new Capsule{circle.getFillColor()}};
	OnlyDrawable::copy(capsule);
	Layout::copy(capsule);
	capsule->resize(size, position);
	return capsule;
}
