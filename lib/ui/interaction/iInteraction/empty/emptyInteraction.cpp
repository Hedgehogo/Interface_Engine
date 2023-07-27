#include "emptyInteraction.hpp"

namespace ui {
	void EmptyInteraction::start(sf::Vector2i mousePosition) {
	}
	
	void EmptyInteraction::update(sf::Vector2i mousePosition) {
	}
	
	void EmptyInteraction::finish(sf::Vector2i mousePosition) {
	}
	
	EmptyInteraction* EmptyInteraction::copy() {
		return new EmptyInteraction{};
	}
	
	bool DecodePointer<EmptyInteraction>::decodePointer(const YAML::Node& node, EmptyInteraction*& emptyInteraction) {
		{
			emptyInteraction = new EmptyInteraction{};
			return true;
		}
	}
}
