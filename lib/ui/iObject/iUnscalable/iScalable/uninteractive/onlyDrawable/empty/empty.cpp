#include "empty.hpp"

namespace ui {
	void Empty::draw() {}
	
	void Empty::resize(sf::Vector2f size, sf::Vector2f position) {
		Layout::resize(size, position);
	}
	
	bool Empty::updateInteractions(sf::Vector2f) {
		return false;
	}
	
	sf::Vector2f Empty::getMinSize() {
		return {};
	}
	
	sf::Vector2f Empty::getNormalSize() {
		return {};
	}
	
	Empty *Empty::copy() {
		Empty *empty{new Empty{}};
		Layout::copy(empty);
		return empty;
	}
	
	void Empty::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
	}
	
	bool convertPointer(const YAML::Node &node, Empty *&empty) {
		{ empty = new Empty{}; return true; }
	}
}
