#include "EmptyInteraction.hpp"

namespace ui {
	EmptyInteraction::EmptyInteraction() {
	}
	
	void EmptyInteraction::start(sf::Vector2i) {
	}
	
	void EmptyInteraction::update(sf::Vector2i) {
	}
	
	void EmptyInteraction::finish(sf::Vector2i) {
	}
	
	EmptyInteraction* EmptyInteraction::copy() {
		return new EmptyInteraction{};
	}
	
	bool DecodePointer<EmptyInteraction>::decodePointer(const YAML::Node&, EmptyInteraction*& emptyInteraction) {
		{
			emptyInteraction = new EmptyInteraction{};
			return true;
		}
	}
}
