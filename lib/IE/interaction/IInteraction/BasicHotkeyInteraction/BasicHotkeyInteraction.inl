namespace ie {
	namespace detail {
		namespace make_system {
			template<typename T>
			BasicHotkeyInteractionHotkey<T>::BasicHotkeyInteractionHotkey(
				bp::BoxPtr<make_system::BasicKeysInteraction<T> >&& interaction,
				size_t state
			) : interaction(std::move(interaction)), state(state) {
			}
			
			template<typename T>
			auto BasicHotkeyInteractionHotkey<T>::make(BasicActionInitInfo<T> init_info) -> detail::BasicHotkeyInteractionHotkey<T>* {
				return new detail::BasicHotkeyInteractionHotkey<T>{std::move(*this), init_info};
			}
		}
		
		template<typename T>
		BasicHotkeyInteractionHotkey<T>::BasicHotkeyInteractionHotkey(Make&& make, BasicActionInitInfo<T> init_info) :
			interaction_(make.interaction->make(init_info)), state_(make.state) {
		}
		
		template<typename T>
		BasicHotkeyInteractionHotkey<T>::BasicHotkeyInteractionHotkey(bp::BoxPtr<BasicKeysInteraction<T> >&& interaction, size_t state) :
			interaction_(std::move(interaction)), state_(state) {
		}
		
		template<typename T>
		BasicHotkeyInteractionHotkey<T>::BasicHotkeyInteractionHotkey(size_t state) :
			interaction_(nullptr), state_(state) {
		}
	}
	
	namespace make_system {
		template<typename T>
		BasicHotkeyInteraction<T>::BasicHotkeyInteraction(std::vector<std::vector<Hotkey> > hotkeys, size_t state) :
			hotkeys(std::move(hotkeys)), state(state) {
		}
		
		template<typename T>
		auto BasicHotkeyInteraction<T>::make(BasicActionInitInfo<T> init_info) -> ie::BasicHotkeyInteraction<T>* {
			return new ie::BasicHotkeyInteraction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicHotkeyInteraction<T>::BasicHotkeyInteraction(Make&& make, BasicActionInitInfo<T> init_info) :
		hotkey_states_(map_make(std::move(make.hotkeys), init_info)), now_hotkeys_(&hotkey_states_[make.state]) {
	}
	
	template<typename T>
	auto BasicHotkeyInteraction<T>::set_hotkey_action(size_t state, Hotkey* hotkey_action) -> void {
		if(hotkey_states_.size() <= state) {
			hotkey_states_.resize(state, {});
		}
		hotkey_states_[state].emplace_back(hotkey_action);
	}
	
	template<typename T>
	auto BasicHotkeyInteraction<T>::get_hotkeys(int state) -> std::vector<Hotkey> {
		return hotkey_states_[state];
	}
	
	template<typename T>
	auto BasicHotkeyInteraction<T>::get_hotkey(int state, int i) -> Hotkey {
		return hotkey_states_[state][i];
	}
	
	template<typename T>
	auto BasicHotkeyInteraction<T>::start(sf::Vector2i mouse_position) -> void {
		for(auto& hotkey: *now_hotkeys_) {
			hotkey.interaction_->start(mouse_position);
		}
	}
	
	template<typename T>
	auto BasicHotkeyInteraction<T>::update(sf::Vector2i mouse_position) -> void {
		for(auto& hotkey: *now_hotkeys_) {
			hotkey.interaction_->update(mouse_position);
			if(hotkey.interaction_->is_press() && hotkey.state_ != std::numeric_limits<size_t>::max()) {
				finish(mouse_position);
				now_hotkeys_ = &hotkey_states_[hotkey.state_];
				start(mouse_position);
			}
		}
	}
	
	template<typename T>
	auto BasicHotkeyInteraction<T>::finish(sf::Vector2i mouse_position) -> void {
		for(auto& hotkey: *now_hotkeys_) {
			hotkey.interaction_->finish(mouse_position);
		}
	}
}

template<typename T>
auto ieml::Decode<char, ie::detail::make_system::BasicHotkeyInteractionHotkey<T> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::detail::make_system::BasicHotkeyInteractionHotkey<T> > {
	auto map{node.get_map_view().except()};
	return ie::detail::make_system::BasicHotkeyInteractionHotkey<T>{
		map.at("interaction").except().as<bp::BoxPtr<ie::make_system::BasicKeysInteraction<T> > >().except(),
		map.get_as<size_t>("state").except().ok_or(std::numeric_limits<size_t>::max())
	};
}

template<typename T>
auto ieml::Decode<char, ie::make_system::BasicHotkeyInteraction<T> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::make_system::BasicHotkeyInteraction<T> > {
	auto map{node.get_map_view().except()};
	return ie::make_system::BasicHotkeyInteraction<T>{
		map.at("hotkeys").except().as<std::vector<std::vector<ie::detail::make_system::BasicHotkeyInteractionHotkey<T> > > >().except(),
		map.get_as<size_t>("state").except().ok_or(0)
	};
}

