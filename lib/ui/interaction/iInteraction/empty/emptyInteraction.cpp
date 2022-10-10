#include "emptyInteraction.hpp"

namespace ui {
	void EmptyInteraction::start(sf::Vector2i mousePosition) {}
	
	bool EmptyInteraction::update(sf::Vector2i mousePosition) {
		return false;
	}
	
	void EmptyInteraction::finish(sf::Vector2i mousePosition) {}
	
	EmptyInteraction *EmptyInteraction::copy() {
		return new EmptyInteraction{};
	}
	
	bool convertPointer(const YAML::Node &node, EmptyInteraction *&emptyInteraction) {
		{ emptyInteraction = new EmptyInteraction{}; return true; }
	}
}
