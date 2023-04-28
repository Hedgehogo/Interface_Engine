#include "keysInteraction.hpp"
#include "../../event/key/openUrl/openUrlEvent.hpp"

namespace ui {
	KeysInteraction::KeysInteraction(KeyEvent* event, std::vector<Key> keys, std::vector<Key> blackListKeys) : event(event), keys(keys), blackListKeys(blackListKeys), press(false) {
		std::sort(this->keys.begin(), this->keys.end());
	}
	
	KeysInteraction::~KeysInteraction() {
		delete event;
	}
	
	std::vector<Key> KeysInteraction::getKeys() {
		return keys;
	}
	
	KeyEvent* KeysInteraction::getEvent() {
		return event;
	}
	
	void KeysInteraction::setEvent(KeyEvent* event) {
		delete this->event;
		this->event = event;
	}
	
	void KeysInteraction::start(sf::Vector2i) {
	}
	
	void KeysInteraction::update(sf::Vector2i mousePosition) {
		press = true;
		for(auto& key: keys) {
			if(!KeyHandler::isKeyPressed(key)) {
				press = false;
				break;
			}
		}
		if(press) {
			for(auto& key: blackListKeys) {
				if(KeyHandler::isKeyPressed(key)) {
					press = false;
					break;
				}
			}
		}
		event->update(mousePosition, press);
	}
	
	void KeysInteraction::finish(sf::Vector2i mousePosition) {
		event->setPressed(false);
	}
	
	bool KeysInteraction::isPress() {
		return press;
	}
	
	KeysInteraction* KeysInteraction::copy() {
		return new KeysInteraction{event->copy(), keys, blackListKeys};
	}
	
	bool convertPointer(const YAML::Node &node, KeysInteraction *&keysInteraction) {
		if(node.IsScalar()) {
			keysInteraction = new KeysInteraction{new OpenUrlEvent{node.as<std::string>()}, {Key::mouseLeft}};
			return true;
		}
		
		KeyEvent* event;
		std::vector<Key> keys;
		std::vector<Key> blackListKeys{};
		
		node["event"] >> event;
		
		keys.resize(node["keys"].size());
		uint i{0};
		for(auto& key: node["keys"]) {
			key >> keys[i];
			++i;
		}
		
		if(node["black-listKeys"]) {
			i = 0;
			for(auto& key: node["black-listKeys"]) {
				key >> blackListKeys[i];
				++i;
			}
		}
		
		{
			keysInteraction = new KeysInteraction{event, keys, blackListKeys};
			return true;
		}
	}
	
	bool DecodePointer<KeysInteraction>::decodePointer(const YAML::Node &node, KeysInteraction *&keysInteraction) {
		if(node.IsScalar()) {
			keysInteraction = new KeysInteraction{new OpenUrlEvent{node.as<std::string>()}, {Key::mouseLeft}};
			return true;
		}
		
		KeyEvent* event;
		std::vector<Key> keys;
		std::vector<Key> blackListKeys{};
		
		node["event"] >> event;
		
		keys.resize(node["keys"].size());
		uint i{0};
		for(auto& key: node["keys"]) {
			key >> keys[i];
			++i;
		}
		
		if(node["black-listKeys"]) {
			i = 0;
			for(auto& key: node["black-listKeys"]) {
				key >> blackListKeys[i];
				++i;
			}
		}
		
		{
			keysInteraction = new KeysInteraction{event, keys, blackListKeys};
			return true;
		}
	}
}