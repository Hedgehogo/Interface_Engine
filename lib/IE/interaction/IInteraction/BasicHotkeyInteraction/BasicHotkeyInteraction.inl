namespace ie {
	namespace detail {
		namespace make_system {
			template<typename T>
			BasicHotkeyInteractionHotkey<T>::BasicHotkeyInteractionHotkey(
				BoxPtr<make_system::BasicKeysInteraction<T> >&& interaction, uint state
			) : interaction(std::move(interaction)), state(state) {
			}
			
			template<typename T>
			detail::BasicHotkeyInteractionHotkey<T>* BasicHotkeyInteractionHotkey<T>::make(BasicActionInitInfo<T> init_info) {
				return new detail::BasicHotkeyInteractionHotkey<T>{std::move(*this), init_info};
			}
		}
		
		template<typename T>
		BasicHotkeyInteractionHotkey<T>::BasicHotkeyInteractionHotkey(Make&& make, BasicActionInitInfo<T> init_info) :
			interaction(make.interaction->make(init_info)), state(make.state) {
		}
		
		template<typename T>
		BasicHotkeyInteractionHotkey<T>::BasicHotkeyInteractionHotkey(BoxPtr<BasicKeysInteraction<T> >&& interaction, uint state) :
			interaction(std::move(interaction)), state(state) {
		}
		
		template<typename T>
		BasicHotkeyInteractionHotkey<T>::BasicHotkeyInteractionHotkey(uint state) :
			interaction(nullptr), state(state) {
		}
	}
	
	namespace make_system {
		template<typename T>
		BasicHotkeyInteraction<T>::BasicHotkeyInteraction(std::vector<std::vector<BoxPtr<Hotkey> > >&& hotkeys, uint state) :
			hotkeys(std::move(hotkeys)), state(state) {
		}
		
		template<typename T>
		ie::BasicHotkeyInteraction<T>* BasicHotkeyInteraction<T>::make(BasicActionInitInfo<T> init_info) {
			return new ie::BasicHotkeyInteraction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicHotkeyInteraction<T>::BasicHotkeyInteraction(Make&& make, BasicActionInitInfo<T> init_info) :
		hotkey_states(map_make(std::move(make.hotkeys), init_info)), now_hotkeys(nullptr) {
		if(hotkey_states.size() <= make.state) {
			hotkey_states.resize(make.state, {});
		}
		now_hotkeys = &hotkey_states[make.state];
	}
	
	template<typename T>
	BasicHotkeyInteraction<T>::BasicHotkeyInteraction(std::vector<std::vector<BoxPtr<Hotkey> > >&& hotkeys, uint state) :
		hotkey_states(std::move(hotkeys)), now_hotkeys(nullptr) {
		if(this->hotkey_states.size() <= state) {
			this->hotkey_states.resize(state, {});
		}
		now_hotkeys = &this->hotkey_states[state];
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::init(BasicActionInitInfo<T> init_info) {
		for(const auto& hotkey_state: hotkey_states) {
			for(auto& hotkey: hotkey_state) {
				hotkey->interaction->init(init_info);
			}
		}
	}
	
	template<typename T>
	BasicHotkeyInteraction<T>::BasicHotkeyInteraction(std::string) {
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::set_hotkey_action(uint state, typename BasicHotkeyInteraction<T>::Hotkey* hotkey_action) {
		if(hotkey_states.size() <= state) {
			hotkey_states.resize(state, {});
		}
		hotkey_states[state].emplace_back(hotkey_action);
	}
	
	template<typename T>
	std::vector<BoxPtr<typename BasicHotkeyInteraction<T>::Hotkey> > BasicHotkeyInteraction<T>::get_hotkeys(int state) {
		return hotkey_states[state];
	}
	
	template<typename T>
	BoxPtr<typename BasicHotkeyInteraction<T>::Hotkey> BasicHotkeyInteraction<T>::get_hotkey(int state, int i) {
		return hotkey_states[state][i];
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::start(sf::Vector2i mouse_position) {
		for(auto& hotkey: *now_hotkeys) {
			hotkey->interaction->start(mouse_position);
		}
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::update(sf::Vector2i mouse_position) {
		for(auto& hotkey: *now_hotkeys) {
			hotkey->interaction->update(mouse_position);
			if(hotkey->interaction->is_press() && hotkey->state != std::numeric_limits<uint>::max()) {
				finish(mouse_position);
				now_hotkeys = &hotkey_states[hotkey->state];
				start(mouse_position);
			}
		}
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::finish(sf::Vector2i mouse_position) {
		for(auto& hotkey: *now_hotkeys) {
			hotkey->interaction->finish(mouse_position);
		}
	}
	
	template<typename T>
	BasicHotkeyInteraction<T>* BasicHotkeyInteraction<T>::copy() {
		return new BasicHotkeyInteraction<T>{*this};
	}
	
	template<typename T>
	bool Decode<detail::BasicHotkeyInteractionHotkey<T>*>::decode(const YAML::Node& node, detail::BasicHotkeyInteractionHotkey<T>*& hotkey) {
		hotkey = new detail::BasicHotkeyInteractionHotkey<T>{
			conv_def(node["interaction"], BoxPtr<BasicKeysInteraction<T> >{}),
			conv_def(node["state"], std::numeric_limits<uint>::max())
		};
		return true;
	}
}