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
		event->update(mousePosition, isKeyPressed(button));
		return false;
	}
	
	void OneButtonInteraction::finish(sf::Vector2i mousePosition) {
		event->setPressed(false);
	}
	
	OneButtonInteraction *OneButtonInteraction::copy() {
		return new OneButtonInteraction{event->copy(), button};
	}
	
	OneButtonInteraction *OneButtonInteraction::createFromYaml(const YAML::Node &node) {
		ButtonEvent *event;
		Key button{Key::mouseLeft};
		
		node["event"] >> event;
		if(node["button"])
			button = createKeyFromYaml(node["button"]);
		
		return new OneButtonInteraction{event, button};
	}
}
