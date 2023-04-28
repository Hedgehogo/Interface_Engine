#include "oneKeyInteraction.hpp"

namespace ui {
	OneKeyInteraction::OneKeyInteraction(KeyEvent* event, Key key) : event(event), key(key) {
	}
	
	OneKeyInteraction::~OneKeyInteraction() {
		delete event;
	}
	
	Key OneKeyInteraction::getKey() {
		return key;
	}
	
	KeyEvent* OneKeyInteraction::getEvent() {
		return event;
	}
	
	void OneKeyInteraction::setEvent(KeyEvent* event) {
		delete this->event;
		this->event = event;
	}
	
	void OneKeyInteraction::start(sf::Vector2i) {
	}
	
	void OneKeyInteraction::update(sf::Vector2i mousePosition) {
		event->update(mousePosition, KeyHandler::isKeyPressed(key));
	}
	
	void OneKeyInteraction::finish(sf::Vector2i mousePosition) {
		event->setPressed(false);
	}
	
	OneKeyInteraction* OneKeyInteraction::copy() {
		return new OneKeyInteraction{event->copy(), key};
	}
	
	
	bool DecodePointer<OneKeyInteraction>::decodePointer(const YAML::Node& node, OneKeyInteraction*& oneKeyInteraction) {
		KeyEvent* event;
		Key key{Key::mouseLeft};
		
		node["event"] >> event;
		if(node["key"])
			node["key"] >> key;
		
		{
			oneKeyInteraction = new OneKeyInteraction{event, key};
			return true;
		}
	}
}
