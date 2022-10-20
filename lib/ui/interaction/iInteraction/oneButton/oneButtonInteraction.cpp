#include "oneButtonInteraction.hpp"

namespace ui {
	OneButtonInteraction::OneButtonInteraction(ButtonEvent *event, Key button) : event(event), button(button) {}
	
	OneButtonInteraction::~OneButtonInteraction() {
		delete event;
	}
	
	Key OneButtonInteraction::getButton() {
		return button;
	}
	
	ButtonEvent *OneButtonInteraction::getEvent() {
		return event;
	}
	
	void OneButtonInteraction::setEvent(ButtonEvent *event) {
		delete this->event;
		this->event = event;
	}
	
	void OneButtonInteraction::start(sf::Vector2i) {
	}
	
	bool OneButtonInteraction::update(sf::Vector2i mousePosition) {
		event->update(mousePosition, KeyHandler::isKeyPressed(button));
		return false;
	}
	
	void OneButtonInteraction::finish(sf::Vector2i mousePosition) {
		event->setPressed(false);
	}
	
	OneButtonInteraction *OneButtonInteraction::copy() {
		return new OneButtonInteraction{event->copy(), button};
	}
	
	bool convertPointer(const YAML::Node &node, OneButtonInteraction *&oneButtonInteraction) {
		ButtonEvent *event;
		Key button{Key::mouseLeft};
		
		node["event"] >> event;
		if(node["button"])
			node["button"] >> button;
		
		{ oneButtonInteraction = new OneButtonInteraction{event, button}; return true; }
	}
}
