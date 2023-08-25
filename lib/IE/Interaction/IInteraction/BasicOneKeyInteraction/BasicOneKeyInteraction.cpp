#include "BasicOneKeyInteraction.hpp"

namespace ui {
	OneKeyInteraction::OneKeyInteraction(BoxPtr<KeyEvent>&& event, Key key) : event(std::move(event)), key(key) {
	}
	
	Key OneKeyInteraction::getKey() {
		return key;
	}
	
	KeyEvent& OneKeyInteraction::getEvent() {
		return *event;
	}
	
	const KeyEvent& OneKeyInteraction::getEvent() const {
		return *event;
	}
	
	void OneKeyInteraction::setEvent(BoxPtr<KeyEvent>&& event) {
		this->event = std::move(event);
	}
	
	void OneKeyInteraction::start(sf::Vector2i) {
	}
	
	void OneKeyInteraction::update(sf::Vector2i mousePosition) {
		event->update(mousePosition, KeyHandler::isKeyPressed(key));
	}
	
	void OneKeyInteraction::finish(sf::Vector2i) {
		event->setPressed(false);
	}
	
	OneKeyInteraction* OneKeyInteraction::copy() {
		return new OneKeyInteraction{*this};
	}
	
	void OneKeyInteraction::init(InteractionInitInfo interactionInitInfo) {
		event->init(interactionInitInfo);
	}
	
	bool DecodePointer<OneKeyInteraction>::decodePointer(const YAML::Node& node, OneKeyInteraction*& oneKeyInteraction) {
		oneKeyInteraction = new OneKeyInteraction{
			node["event"].as<BoxPtr<KeyEvent> >(),
			convDef(node["key"], Key::mouseLeft)
		};
		return true;
	}
}
