#include <utility>

#include "../../IAction/IBasicActivityAction/BasicOpenUrlAction/BasicOpenUrlAction.hpp"

namespace ie {
	namespace make_system {
		template<typename A_>
		BasicKeysInteraction<A_>::BasicKeysInteraction(BoxPtr<IBasicTouchAction<A_> >&& action, std::vector<Key> keys, std::vector<Key> black_list_keys) :
			action(std::move(action)), keys(std::move(keys)), black_list_keys(std::move(black_list_keys)) {
		}
		
		template<typename A_>
		auto BasicKeysInteraction<A_>::make(BasicActionInitInfo<A_> init_info) -> ie::BasicKeysInteraction<A_>* {
			return new ie::BasicKeysInteraction<A_>{std::move(*this), init_info};
		}
	}
	
	template<typename A_>
	BasicKeysInteraction<A_>::BasicKeysInteraction(Make&& make, BasicActionInitInfo<A_> init_info) :
		event_handler_(&init_info.event_handler),
		action_(make.action->make(init_info)),
		keys_(std::move(make.keys)),
		black_list_keys_(std::move(make.black_list_keys)),
		press_(false) {
		std::sort(keys_.begin(), keys_.end());
	}
	
	template<typename A_>
	auto BasicKeysInteraction<A_>::get_keys() -> std::vector<Key> {
		return keys_;
	}
	
	template<typename A_>
	auto BasicKeysInteraction<A_>::get_action() -> IBasicTouchAction<A_>* {
		return action_.get();
	}
	
	template<typename A_>
	auto BasicKeysInteraction<A_>::set_action(IBasicTouchAction<A_>* action) -> void {
		this->action_.reset(action);
	}
	
	template<typename A_>
	auto BasicKeysInteraction<A_>::start(sf::Vector2i) -> void {
	}
	
	template<typename A_>
	auto BasicKeysInteraction<A_>::handle_event(Event event) -> bool {
		return false;
	}
	
	template<typename A_>
	auto BasicKeysInteraction<A_>::update(sf::Vector2i mouse_position) -> void {
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
		action_->update({{mouse_position, press_}});
	}
	
	template<typename A_>
	auto BasicKeysInteraction<A_>::finish(sf::Vector2i) -> void {
		action_->finish();
	}
	
	template<typename A_>
	auto BasicKeysInteraction<A_>::is_press() const -> bool {
		return press_;
	}
}

template<typename A_>
auto ieml::Decode<char, ie::make_system::BasicKeysInteraction<A_> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::make_system::BasicKeysInteraction<A_> > {
	auto& clear_node{node.get_clear()};
	//old_action
	/*for(auto& str: clear_node.get_string().ok_or_none()) {
		return ie::make_system::BasicKeysInteraction<A_>{
			bp::make_box_ptr<ie::make_system::BasicTouchAction<A_>, ie::make_system::BasicOpenUrlAction<A_> >(str),
			std::vector{ie::Key::MouseLeft},
		};
	}*/
	auto map{clear_node.get_map_view().except()};
	return ie::make_system::BasicKeysInteraction<A_>{
		map.at("action").except().as<ie::BoxPtr<ie::make_system::IBasicTouchAction<A_> > >().except(),
		map.at("keys").except().as<std::vector<ie::Key> >().except(),
		map.get_as<std::vector<ie::Key> >("black-list-keys").except().ok_or({}),
	};
}
