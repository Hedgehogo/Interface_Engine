#include "BasicKeysInteraction.hpp"

#include <utility>
#include "../../IEvent/BasicKeyEvent/BasicOpenUrlEvent/BasicOpenUrlEvent.hpp"

namespace ui {
	KeysInteraction::KeysInteraction(BoxPtr<KeyEvent>&& event, std::vector<Key> keys, std::vector<Key> blackListKeys) : event(std::move(event)), keys(std::move(keys)), blackListKeys(std::move(blackListKeys)), press(false) {
		std::sort(this->keys.begin(), this->keys.end());
	}
	
	std::vector<Key> KeysInteraction::getKeys() {
		return keys;
	}
	
	KeyEvent* KeysInteraction::getEvent() {
		return event.get();
	}
	
	void KeysInteraction::setEvent(KeyEvent* event) {
		this->event.reset(event);
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
	
	void KeysInteraction::finish(sf::Vector2i) {
		event->setPressed(false);
	}
	
	bool KeysInteraction::isPress() const {
		return press;
	}
	
	KeysInteraction* KeysInteraction::copy() {
		return new KeysInteraction{*this};
	}
	
	bool DecodePointer<KeysInteraction>::decodePointer(const YAML::Node& node, KeysInteraction*& keysInteraction) {
		if(node.IsScalar()) {
			keysInteraction = new KeysInteraction{makeBoxPtr<KeyEvent, OpenUrlEvent>(node.as<std::string>()), {Key::mouseLeft}};
			return true;
		}
		
		keysInteraction = new KeysInteraction{
			node["event"].as<BoxPtr<KeyEvent>>(),
			node["keys"].as<std::vector<Key>>(),
			convDef<std::vector<Key>>(node["black-listKeys"], {})
		};
		return true;
	}
}