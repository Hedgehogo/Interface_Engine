//
// Created by Professional on 31.03.2022.
//

#include "doubleInteraction.h"

ui::DoubleInteraction::DoubleInteraction(ui::IInteraction *first, ui::IInteraction *second) :
	first(first), second(second) {}

ui::DoubleInteraction::~DoubleInteraction() {
	delete first;
	delete second;
}

void ui::DoubleInteraction::setFirst(ui::IInteraction *first) {
	delete this->first;
	this->first = first;
}

void ui::DoubleInteraction::setSecond(ui::IInteraction *second) {
	delete this->second;
	this->second = second;
}

ui::IInteraction *ui::DoubleInteraction::getFirst() {
	return first;
}

ui::IInteraction *ui::DoubleInteraction::getSecond() {
	return second;
}

void ui::DoubleInteraction::start(sf::Vector2i mousePosition) {
	if(first != nullptr) {
		first->start(mousePosition);
	}
	if(second != nullptr) {
		second->start(mousePosition);
	}
}

bool ui::DoubleInteraction::update(sf::Vector2i mousePosition) {
	if(first != nullptr) {
		first->update(mousePosition);
	}
	if(second != nullptr) {
		second->update(mousePosition);
	}
	return false;
}

void ui::DoubleInteraction::finish(sf::Vector2i mousePosition) {
	if(second != nullptr) {
		second->finish(mousePosition);
	}
	if(first != nullptr) {
		first->finish(mousePosition);
	}
}

ui::DoubleInteraction *ui::DoubleInteraction::copy() {
	return new DoubleInteraction{first->copy(), second->copy()};
}
