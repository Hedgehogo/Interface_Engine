namespace ie {
	namespace detail {
		namespace make_system {
			template<typename T>
			BasicHotkeyInteractionHotkey<T>::BasicHotkeyInteractionHotkey(
				BoxPtr<make_system::BasicKeysInteraction<T> >&& interaction, size_t state
			) : interaction(std::move(interaction)), state(state) {
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
		BasicHotkeyInteractionHotkey<T>::BasicHotkeyInteractionHotkey(BoxPtr<BasicKeysInteraction<T> >&& interaction, size_t state) :
			interaction_(std::move(interaction)), state_(state) {
		}
		
		template<typename T>
		BasicHotkeyInteractionHotkey<T>::BasicHotkeyInteractionHotkey(size_t state) :
			interaction_(nullptr), state_(state) {
		}
	}
	
	namespace make_system {
		template<typename T>
		BasicHotkeyInteraction<T>::BasicHotkeyInteraction(std::vector<std::vector<BoxPtr<Hotkey> > >&& hotkeys, size_t state) :
			hotkeys(std::move(hotkeys)), state(state) {
		}
		
		template<typename T>
		ie::BasicHotkeyInteraction<T>* BasicHotkeyInteraction<T>::make(BasicActionInitInfo<T> init_info) {
			return new ie::BasicHotkeyInteraction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicHotkeyInteraction<T>::BasicHotkeyInteraction(Make&& make, BasicActionInitInfo<T> init_info) :
		hotkey_states_(map_make(std::move(make.hotkeys), init_info)), now_hotkeys_(nullptr) {
		if(hotkey_states_.size() <= make.state) {
			hotkey_states_.resize(make.state, {});
		}
		now_hotkeys_ = &hotkey_states_[make.state];
	}
	
	template<typename T>
	BasicHotkeyInteraction<T>::BasicHotkeyInteraction(std::vector<std::vector<BoxPtr<Hotkey> > >&& hotkeys, size_t state) :
		hotkey_states_(std::move(hotkeys)), now_hotkeys_(nullptr) {
		if(this->hotkey_states_.size() <= state) {
			this->hotkey_states_.resize(state, {});
		}
		now_hotkeys_ = &this->hotkey_states_[state];
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::init(BasicActionInitInfo<T> init_info) {
		for(const auto& hotkey_state: hotkey_states_) {
			for(auto& hotkey: hotkey_state) {
				hotkey->interaction_->init(init_info);
			}
		}
	}
	
	template<typename T>
	BasicHotkeyInteraction<T>::BasicHotkeyInteraction(std::string) {
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::set_hotkey_action(size_t state, typename BasicHotkeyInteraction<T>::Hotkey* hotkey_action) {
		if(hotkey_states_.size() <= state) {
			hotkey_states_.resize(state, {});
		}
		hotkey_states_[state].emplace_back(hotkey_action);
	}
	
	template<typename T>
	std::vector<BoxPtr<typename BasicHotkeyInteraction<T>::Hotkey> > BasicHotkeyInteraction<T>::get_hotkeys(int state) {
		return hotkey_states_[state];
	}
	
	template<typename T>
	BoxPtr<typename BasicHotkeyInteraction<T>::Hotkey> BasicHotkeyInteraction<T>::get_hotkey(int state, int i) {
		return hotkey_states_[state][i];
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::start(sf::Vector2i mouse_position) {
		for(auto& hotkey: *now_hotkeys_) {
			hotkey->interaction_->start(mouse_position);
		}
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::update(sf::Vector2i mouse_position) {
		for(auto& hotkey: *now_hotkeys_) {
			hotkey->interaction_->update(mouse_position);
			if(hotkey->interaction_->is_press() && hotkey->state_ != std::numeric_limits<size_t>::max()) {
				finish(mouse_position);
				now_hotkeys_ = &hotkey_states_[hotkey->state_];
				start(mouse_position);
			}
		}
	}
	
	template<typename T>
	void BasicHotkeyInteraction<T>::finish(sf::Vector2i mouse_position) {
		for(auto& hotkey: *now_hotkeys_) {
			hotkey->interaction_->finish(mouse_position);
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
			conv_def(node["state"], std::numeric_limits<size_t>::max())
		};
		return true;
	}
}