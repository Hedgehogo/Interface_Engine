#include <utility>

namespace ui {
	template<typename T>
	BasicKeysInteraction<T>::BasicKeysInteraction(BoxPtr<BasicKeyEvent<T> >&& event, std::vector<Key> keys, std::vector<Key> blackListKeys) :
		event(std::move(event)), keys(std::move(keys)), blackListKeys(std::move(blackListKeys)), press(false) {
		std::sort(this->keys.begin(), this->keys.end());
	}
	
	template<typename T>
	std::vector<Key> BasicKeysInteraction<T>::getKeys() {
		return keys;
	}
	
	template<typename T>
	BasicKeyEvent<T>* BasicKeysInteraction<T>::getEvent() {
		return event.get();
	}
	
	template<typename T>
	void BasicKeysInteraction<T>::setEvent(BasicKeyEvent<T>* event) {
		this->event.reset(event);
	}
	
	template<typename T>
	void BasicKeysInteraction<T>::start(sf::Vector2i) {
	}
	
	template<typename T>
	void BasicKeysInteraction<T>::update(sf::Vector2i mousePosition) {
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
	
	template<typename T>
	void BasicKeysInteraction<T>::finish(sf::Vector2i) {
		event->setPressed(false);
	}
	
	template<typename T>
	bool BasicKeysInteraction<T>::isPress() const {
		return press;
	}
	
	template<typename T>
	BasicKeysInteraction<T>* BasicKeysInteraction<T>::copy() {
		return new BasicKeysInteraction<T>{*this};
	}
	
	template<typename T>
	bool DecodePointer<BasicKeysInteraction<T> >::decodePointer(const YAML::Node& node, BasicKeysInteraction<T> *& keysInteraction) {
		if(node.IsScalar()) {
			keysInteraction = new BasicKeysInteraction<T>{makeBoxPtr<BasicKeyEvent<T>, BasicOpenUrlEvent<T> >(node.as<std::string>()), {Key::mouseLeft}};
			return true;
		}
		
		keysInteraction = new BasicKeysInteraction<T>{
			node["event"].as<BoxPtr<BasicKeyEvent<T> > >(),
			node["keys"].as<std::vector<Key> >(),
			convDef<std::vector<Key> >(node["black-listKeys"], {})
		};
		return true;
	}
}