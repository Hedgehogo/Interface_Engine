#include <utility>

#include "IE/Interaction/IAction/BasicKeyAction/BasicOpenUrlAction/BasicOpenUrlAction.hpp"

namespace ie {
	namespace make_system {
		template<typename T>
		BasicKeysInteraction<T>::BasicKeysInteraction(BoxPtr<ie::BasicKeyAction<T> >&& action, std::vector<Key> keys, std::vector<Key> blackListKeys) :
			action(std::move(action)), keys(std::move(keys)), blackListKeys(std::move(blackListKeys)) {
		}
		
		template<typename T>
		ie::BasicKeysInteraction<T>* BasicKeysInteraction<T>::make(BasicActionInitInfo<T> initInfo) {
			return new ie::BasicKeysInteraction<T>{std::move(*this), initInfo};
		}
	}
	
	template<typename T>
	BasicKeysInteraction<T>::BasicKeysInteraction(Make&& make, BasicActionInitInfo<T> initInfo) :
		action(make.action->make(initInfo)), keys(std::move(make.keys)), blackListKeys(std::move(make.blackListKeys)), press(false) {
		std::sort(this->keys.begin(), this->keys.end());
	}
	
	template<typename T>
	BasicKeysInteraction<T>::BasicKeysInteraction(BoxPtr<BasicKeyAction<T> >&& action, std::vector<Key> keys, std::vector<Key> blackListKeys) :
		action(std::move(action)), keys(std::move(keys)), blackListKeys(std::move(blackListKeys)), press(false) {
		std::sort(this->keys.begin(), this->keys.end());
	}
	
	template<typename T>
	void BasicKeysInteraction<T>::init(BasicActionInitInfo<T> initInfo) {
		IBasicInteraction<T>::init(initInfo);
		action->init(initInfo);
	}
	
	template<typename T>
	std::vector<Key> BasicKeysInteraction<T>::getKeys() {
		return keys;
	}
	
	template<typename T>
	BasicKeyAction<T>* BasicKeysInteraction<T>::getAction() {
		return action.get();
	}
	
	template<typename T>
	void BasicKeysInteraction<T>::setAction(BasicKeyAction<T>* action) {
		this->action.reset(action);
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
		action->update(mousePosition, press);
	}
	
	template<typename T>
	void BasicKeysInteraction<T>::finish(sf::Vector2i) {
		action->setPressed(false);
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
			keysInteraction = new BasicKeysInteraction<T>{makeBoxPtr<BasicKeyAction<T>, BasicOpenUrlAction<T> >(node.as<std::string>()), {Key::MouseLeft}};
			return true;
		}
		
		keysInteraction = new BasicKeysInteraction<T>{
			node["action"].as<BoxPtr<BasicKeyAction<T> > >(),
			node["keys"].as<std::vector<Key> >(),
			convDef<std::vector<Key> >(node["black-listKeys"], {})
		};
		return true;
	}
}