#include <utility>

#include "../../IAction/IBasicActivityAction/BasicOpenUrlAction/BasicOpenUrlAction.hpp"

namespace ie {
	namespace make_system {
		template<typename T>
		BasicKeysInteraction<T>::BasicKeysInteraction(BoxPtr<IBasicTouchAction<T> >&& action, std::vector<Key> keys, std::vector<Key> black_list_keys) :
			action(std::move(action)), keys(std::move(keys)), black_list_keys(std::move(black_list_keys)) {
		}
		
		template<typename T>
		auto BasicKeysInteraction<T>::make(BasicActionInitInfo<T> init_info) -> ie::BasicKeysInteraction<T>* {
			return new ie::BasicKeysInteraction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicKeysInteraction<T>::BasicKeysInteraction(Make&& make, BasicActionInitInfo<T> init_info) :
		event_handler_(&init_info.event_handler),
		action_(make.action->make(init_info)),
		keys_(std::move(make.keys)),
		black_list_keys_(std::move(make.black_list_keys)),
		press_(false) {
		std::sort(keys_.begin(), keys_.end());
	}
	
	template<typename T>
	auto BasicKeysInteraction<T>::get_keys() -> std::vector<Key> {
		return keys_;
	}
	
	template<typename T>
	auto BasicKeysInteraction<T>::get_action() -> IBasicTouchAction<T>* {
		return action_.get();
	}
	
	template<typename T>
	auto BasicKeysInteraction<T>::set_action(IBasicTouchAction<T>* action) -> void {
		this->action_.reset(action);
	}
	
	template<typename T>
	auto BasicKeysInteraction<T>::start(sf::Vector2i) -> void {
	}
	
	template<typename T>
	auto BasicKeysInteraction<T>::update(sf::Vector2i mouse_position) -> void {
		press_ = true;
		for(auto& key: keys_) {
			if(!event_handler_->get_key(key)) {
				press_ = false;
				break;
			}
		}
		if(press_) {
			for(auto& key: black_list_keys_) {
				if(event_handler_->get_key(key)) {
					press_ = false;
					break;
				}
			}
		}
		action_->update(mouse_position, press_);
	}
	
	template<typename T>
	auto BasicKeysInteraction<T>::finish(sf::Vector2i) -> void {
		action_->finish();
	}
	
	template<typename T>
	auto BasicKeysInteraction<T>::is_press() const -> bool {
		return press_;
	}
}

template<typename T>
auto ieml::Decode<char, ie::make_system::BasicKeysInteraction<T> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::make_system::BasicKeysInteraction<T> > {
	auto& clear_node{node.get_clear()};
	//old_action
	/*for(auto& str: clear_node.get_string().ok_or_none()) {
		return ie::make_system::BasicKeysInteraction<T>{
			bp::make_box_ptr<ie::make_system::BasicTouchAction<T>, ie::make_system::BasicOpenUrlAction<T> >(str),
			std::vector{ie::Key::MouseLeft},
		};
	}*/
	auto map{clear_node.get_map_view().except()};
	return ie::make_system::BasicKeysInteraction<T>{
		map.at("action").except().as<ie::BoxPtr<ie::make_system::IBasicTouchAction<T> > >().except(),
		map.at("keys").except().as<std::vector<ie::Key> >().except(),
		map.get_as<std::vector<ie::Key> >("black-list-keys").except().ok_or({}),
	};
}
