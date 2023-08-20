#include "doubleInteraction.hpp"

namespace ui {
	DoubleInteraction::DoubleInteraction(BoxPtr<IInteraction>&& first, BoxPtr<IInteraction>&& second) :
		first(std::move(first)), second(std::move(second)) {
	}
	
	void DoubleInteraction::setFirst(BoxPtr<IInteraction>&& first) {
		this->first = std::move(first);
	}
	
	void DoubleInteraction::setSecond(BoxPtr<IInteraction>&& second) {
		this->second = std::move(second);
	}
	
	IInteraction& DoubleInteraction::getFirst() {
		return *first;
	}
	
	const IInteraction& DoubleInteraction::getFirst() const {
		return *first;
	}
	
	IInteraction& DoubleInteraction::getSecond() {
		return *second;
	}
	
	const IInteraction& DoubleInteraction::getSecond() const {
		return *second;
	}
	
	void DoubleInteraction::start(sf::Vector2i mousePosition) {
		first->start(mousePosition);
		second->start(mousePosition);
	}
	
	void DoubleInteraction::update(sf::Vector2i mousePosition) {
		first->update(mousePosition);
		second->update(mousePosition);
	}
	
	void DoubleInteraction::finish(sf::Vector2i mousePosition) {
		second->finish(mousePosition);
		first->finish(mousePosition);
	}
	
	DoubleInteraction* DoubleInteraction::copy() {
		return new DoubleInteraction{*this};
	}
}
