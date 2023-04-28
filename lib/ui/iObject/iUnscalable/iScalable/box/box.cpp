#include "box.hpp"

namespace ui {
	Box::Box(sf::Vector2f minSize, sf::Vector2f size) :
		Layout(size), minimumSize(minSize) {
	}
	
	void Box::resize(sf::Vector2f size, sf::Vector2f position) {
		Layout::resize(size, position);
	}
	
	void Box::copy(Box* box) {
		Layout::copy(box);
	}
}