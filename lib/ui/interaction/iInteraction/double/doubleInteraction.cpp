#include "doubleInteraction.hpp"

namespace ui {
	DoubleInteraction::DoubleInteraction(IInteraction *first, IInteraction *second) :
		first(first), second(second) {
	}
	
	DoubleInteraction::~DoubleInteraction() {
		delete first;
		delete second;
	}
	
	void DoubleInteraction::setFirst(IInteraction *first) {
		delete this->first;
		this->first = first;
	}
	
	void DoubleInteraction::setSecond(IInteraction *second) {
		delete this->second;
		this->second = second;
	}
	
	IInteraction *DoubleInteraction::getFirst() {
		return first;
	}
	
	IInteraction *DoubleInteraction::getSecond() {
		return second;
	}
	
	void DoubleInteraction::start(sf::Vector2i mousePosition) {
		if(first != nullptr) {
			first->start(mousePosition);
		}
		if(second != nullptr) {
			second->start(mousePosition);
		}
	}
	
	bool DoubleInteraction::update(sf::Vector2i mousePosition) {
		if(first != nullptr) {
			first->update(mousePosition);
		}
		if(second != nullptr) {
			second->update(mousePosition);
		}
		return false;
	}
	
	void DoubleInteraction::finish(sf::Vector2i mousePosition) {
		if(second != nullptr) {
			second->finish(mousePosition);
		}
		if(first != nullptr) {
			first->finish(mousePosition);
		}
	}
	
	DoubleInteraction *DoubleInteraction::copy() {
		return new DoubleInteraction{first->copy(), second->copy()};
	}
}
