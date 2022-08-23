#include "empty.hpp"

void ui::Empty::draw() {}

void ui::Empty::resize(sf::Vector2f size, sf::Vector2f position) {
	Layout::resize(size, position);
}

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
	Empty* empty{new Empty{}};
	Layout::copy(empty);
	return empty;
}

void ui::Empty::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {}

ui::Empty *ui::Empty::createFromYaml(const YAML::Node &node) {
	return new Empty{};
}
