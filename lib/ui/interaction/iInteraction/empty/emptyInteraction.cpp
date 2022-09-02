#include "emptyInteraction.hpp"

void ui::EmptyInteraction::start(sf::Vector2i mousePosition) {}

bool ui::EmptyInteraction::update(sf::Vector2i mousePosition) { return false; }

void ui::EmptyInteraction::finish(sf::Vector2i mousePosition) {}

ui::EmptyInteraction *ui::EmptyInteraction::copy() {
	return new EmptyInteraction{};
}
