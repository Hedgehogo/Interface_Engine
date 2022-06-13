#include "empty.h"

void ui::Empty::draw() {}

void ui::Empty::resize(sf::Vector2f, sf::Vector2f) {}

bool ui::Empty::updateInteractions(sf::Vector2f) {
	return false;
}

sf::Vector2f ui::Empty::getMinSize() {
	return {};
}

sf::Vector2f ui::Empty::getNormalSize() {
	return {};
}

ui::Empty *ui::Empty::copy() {
	return new Empty{};
}
