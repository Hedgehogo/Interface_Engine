namespace ie {
	namespace detail {
		namespace make_system {
			template<typename T>
			BasicHotkeyInteractionHotkey<T>::BasicHotkeyInteractionHotkey(
				bp::BoxPtr<make_system::BasicKeysInteraction<T> >&& interaction,
				size_t state
			) : interaction(std::move(interaction)),
				state(state) {
			}
			
			template<typename T>
			detail::BasicHotkeyInteractionHotkey<T>* BasicHotkeyInteractionHotkey<T>::make(BasicActionInitInfo<T> init_info) {
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
		BasicHotkeyInteraction<T>::BasicHotkeyInteraction(std::vector<std::vector<Hotkey > > hotkeys, size_t state) :
			hotkeys(std::move(hotkeys)), state(state) {
		}
		
		template<typename T>
		ie::BasicHotkeyInteraction<T>* BasicHotkeyInteraction<T>::make(BasicActionInitInfo<T> init_info) {
			return new ie::BasicHotkeyInteraction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicHotkeyInteraction<T>::BasicHotkeyInteraction(Make&& make, BasicActionInitInfo<T> init_info) :
		hotkey_states_(map_make(std::move(make.hotkeys), init_info)), now_hotkeys_(&hotkey_states_[make.state]) {
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::set_hotkey_action(size_t state, typename BasicHotkeyInteraction<T>::Hotkey* hotkey_action) {
		if(hotkey_states_.size() <= state) {
			hotkey_states_.resize(state, {});
		}
		hotkey_states_[state].emplace_back(hotkey_action);
	}
	
	template<typename T>
	std::vector<typename BasicHotkeyInteraction<T>::Hotkey> BasicHotkeyInteraction<T>::get_hotkeys(int state) {
		return hotkey_states_[state];
	}
	
	template<typename T>
	typename BasicHotkeyInteraction<T>::Hotkey BasicHotkeyInteraction<T>::get_hotkey(int state, int i) {
		return hotkey_states_[state][i];
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::start(sf::Vector2i mouse_position) {
		for(auto& hotkey: *now_hotkeys_) {
			hotkey.interaction_->start(mouse_position);
		}
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::update(sf::Vector2i mouse_position) {
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
	void BasicHotkeyInteraction<T>::finish(sf::Vector2i mouse_position) {
		for(auto& hotkey: *now_hotkeys_) {
			hotkey.interaction_->finish(mouse_position);
		}
	}
}

template<typename T>
orl::Option<ie::detail::make_system::BasicHotkeyInteractionHotkey<T> >
ieml::Decode<char, ie::detail::make_system::BasicHotkeyInteractionHotkey<T> >::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::detail::make_system::BasicHotkeyInteractionHotkey<T>{
		map.at("interaction").except().as<bp::BoxPtr<ie::make_system::BasicKeysInteraction<T> > >().except(),
		map.get_as<size_t>("state").except().ok_or(std::numeric_limits<size_t>::max())
	};
}

template<typename T>
orl::Option<ie::make_system::BasicHotkeyInteraction<T> >
ieml::Decode<char, ie::make_system::BasicHotkeyInteraction<T> >::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::make_system::BasicHotkeyInteraction<T>{
		map.at("hotkeys").except().as<std::vector<std::vector<ie::detail::make_system::BasicHotkeyInteractionHotkey<T> > > >().except(),
		map.get_as<size_t>("state").except().ok_or(0)
	};
}

