#include <utility>

#include "../../IAction/BasicKeyAction/BasicOpenUrlAction/BasicOpenUrlAction.hpp"

namespace ie {
	namespace make_system {
		template<typename T>
		BasicKeysInteraction<T>::BasicKeysInteraction(BoxPtr<BasicKeyAction<T> >&& action, std::vector<Key> keys, std::vector<Key> black_list_keys) :
			action(std::move(action)), keys(std::move(keys)), black_list_keys(std::move(black_list_keys)) {
		}
		
		template<typename T>
		ie::BasicKeysInteraction<T>* BasicKeysInteraction<T>::make(BasicActionInitInfo<T> init_info) {
			return new ie::BasicKeysInteraction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicKeysInteraction<T>::BasicKeysInteraction(Make&& make, BasicActionInitInfo<T> init_info) :
		action_(make.action->make(init_info)), keys_(std::move(make.keys)), black_list_keys_(std::move(make.black_list_keys)), press_(false) {
		std::sort(this->keys_.begin(), this->keys_.end());
	}
	
	template<typename T>
	BasicKeysInteraction<T>::BasicKeysInteraction(BoxPtr<BasicKeyAction<T> >&& action, std::vector<Key> keys, std::vector<Key> black_list_keys) :
		action_(std::move(action)), keys_(std::move(keys)), black_list_keys_(std::move(black_list_keys)), press_(false) {
		std::sort(this->keys_.begin(), this->keys_.end());
	}
	
	template<typename T>
	void BasicKeysInteraction<T>::init(BasicActionInitInfo<T> init_info) {
		IBasicInteraction<T>::init(init_info);
		action_->init(init_info);
	}
	
	template<typename T>
	std::vector<Key> BasicKeysInteraction<T>::get_keys() {
		return keys_;
	}
	
	template<typename T>
	BasicKeyAction<T>* BasicKeysInteraction<T>::get_action() {
		return action_.get();
	}
	
	template<typename T>
	void BasicKeysInteraction<T>::set_action(BasicKeyAction<T>* action) {
		this->action_.reset(action);
	}
	
	template<typename T>
	void BasicKeysInteraction<T>::start(sf::Vector2i) {
	}
	
	template<typename T>
	void BasicKeysInteraction<T>::update(sf::Vector2i mouse_position) {
		press_ = true;
		for(auto& key: keys_) {
			if(!KeyHandler::is_key_pressed(key)) {
				press_ = false;
				break;
			}
		}
		if(press_) {
			for(auto& key: black_list_keys_) {
				if(KeyHandler::is_key_pressed(key)) {
					press_ = false;
					break;
				}
			}
		}
		action_->update(mouse_position, press_);
	}
	
	template<typename T>
	void BasicKeysInteraction<T>::finish(sf::Vector2i) {
		action_->set_pressed(false);
	}
	
	template<typename T>
	bool BasicKeysInteraction<T>::is_press() const {
		return press_;
	}
	
	template<typename T>
	BasicKeysInteraction<T>* BasicKeysInteraction<T>::copy() {
		return new BasicKeysInteraction<T>{*this};
	}
}

template<typename T>
orl::Option<ie::make_system::BasicKeysInteraction<T> > ieml::Decode<char, ie::make_system::BasicKeysInteraction<T> >::decode(ieml::Node const& node) {
	auto& clear_node{node.get_clear()};
	if(auto str{clear_node.get_string()}) {
		return ie::make_system::BasicKeysInteraction<T>{
			bp::make_box_ptr<ie::make_system::BasicKeyAction<T>, ie::make_system::BasicOpenUrlAction<T> >(str.ok()),
			std::vector{ie::Key::MouseLeft},
		};
	}
	auto& map{clear_node.get_map_view().except()};
	return ie::make_system::BasicKeysInteraction<T>{
		map.at("action").except().as<ie::BoxPtr<ie::make_system::BasicKeyAction<T> > >().move_except(),
		map.at("keys").except().as<std::vector<ie::Key> >().move_except(),
		map.get_as<std::vector<ie::Key> >("black-list-keys").move_ok_or({}),
	};
}
