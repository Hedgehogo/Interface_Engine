namespace ie {
	namespace detail {
		namespace make_system {
			template<typename A_>
			BasicHotkeyInteractionHotkey<A_>::BasicHotkeyInteractionHotkey(
				bp::BoxPtr<make_system::BasicKeysInteraction<A_> >&& interaction,
				size_t state
			) : interaction(std::move(interaction)), state(state) {
			}
			
			template<typename A_>
			auto BasicHotkeyInteractionHotkey<A_>::make(BasicActionInitInfo<A_> init_info) -> detail::BasicHotkeyInteractionHotkey<A_>* {
				return new detail::BasicHotkeyInteractionHotkey<A_>{std::move(*this), init_info};
			}
		}
		
		template<typename A_>
		BasicHotkeyInteractionHotkey<A_>::BasicHotkeyInteractionHotkey(Make&& make, BasicActionInitInfo<A_> init_info) :
			interaction_(make.interaction->make(init_info)), state_(make.state) {
		}
		
		template<typename A_>
		BasicHotkeyInteractionHotkey<A_>::BasicHotkeyInteractionHotkey(bp::BoxPtr<BasicKeysInteraction<A_> >&& interaction, size_t state) :
			interaction_(std::move(interaction)), state_(state) {
		}
		
		template<typename A_>
		BasicHotkeyInteractionHotkey<A_>::BasicHotkeyInteractionHotkey(size_t state) :
			interaction_(nullptr), state_(state) {
		}
	}
	
	namespace make_system {
		template<typename A_>
		BasicHotkeyInteraction<A_>::BasicHotkeyInteraction(std::vector<std::vector<Hotkey> > hotkeys, size_t state) :
			hotkeys(std::move(hotkeys)), state(state) {
		}
		
		template<typename A_>
		auto BasicHotkeyInteraction<A_>::make(BasicActionInitInfo<A_> init_info) -> ie::BasicHotkeyInteraction<A_>* {
			return new ie::BasicHotkeyInteraction<A_>{std::move(*this), init_info};
		}
	}
	
	template<typename A_>
	BasicHotkeyInteraction<A_>::BasicHotkeyInteraction(Make&& make, BasicActionInitInfo<A_> init_info) :
		hotkey_states_(map_make(std::move(make.hotkeys), init_info)), now_hotkeys_(&hotkey_states_[make.state]) {
	}
	
	template<typename A_>
	auto BasicHotkeyInteraction<A_>::set_hotkey_action(size_t state, Hotkey* hotkey_action) -> void {
		if(hotkey_states_.size() <= state) {
			hotkey_states_.resize(state, {});
		}
		hotkey_states_[state].emplace_back(hotkey_action);
	}
	
	template<typename A_>
	auto BasicHotkeyInteraction<A_>::get_hotkeys(int state) -> std::vector<Hotkey> {
		return hotkey_states_[state];
	}
	
	template<typename A_>
	auto BasicHotkeyInteraction<A_>::get_hotkey(int state, int i) -> Hotkey {
		return hotkey_states_[state][i];
	}
	
	template<typename A_>
	auto BasicHotkeyInteraction<A_>::start() -> void {
		for(auto& hotkey: *now_hotkeys_) {
			hotkey.interaction_->start();
		}
	}
	
	template<typename A_>
	auto BasicHotkeyInteraction<A_>::handle_event(Event event) -> bool {
		/*old_action*/
		return false;
	}
	
	template<typename A_>
	auto BasicHotkeyInteraction<A_>::update() -> void {
		for(auto& hotkey: *now_hotkeys_) {
			hotkey.interaction_->update();
			if(hotkey.interaction_->is_press() && hotkey.state_ != std::numeric_limits<size_t>::max()) {
				finish();
				now_hotkeys_ = &hotkey_states_[hotkey.state_];
				start();
			}
		}
	}
	
	template<typename A_>
	auto BasicHotkeyInteraction<A_>::finish() -> void {
		for(auto& hotkey: *now_hotkeys_) {
			hotkey.interaction_->finish();
		}
	}
}

template<typename A_>
auto ieml::Decode<char, ie::detail::make_system::BasicHotkeyInteractionHotkey<A_> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::detail::make_system::BasicHotkeyInteractionHotkey<A_> > {
	auto map{node.get_map_view().except()};
	return ie::detail::make_system::BasicHotkeyInteractionHotkey<A_>{
		map.at("interaction").except().as<bp::BoxPtr<ie::make_system::BasicKeysInteraction<A_> > >().except(),
		map.get_as<size_t>("state").except().ok_or(std::numeric_limits<size_t>::max())
	};
}

template<typename A_>
auto ieml::Decode<char, ie::make_system::BasicHotkeyInteraction<A_> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::make_system::BasicHotkeyInteraction<A_> > {
	auto map{node.get_map_view().except()};
	return ie::make_system::BasicHotkeyInteraction<A_>{
		map.at("hotkeys").except().as<std::vector<std::vector<ie::detail::make_system::BasicHotkeyInteractionHotkey<A_> > > >().except(),
		map.get_as<size_t>("state").except().ok_or(0)
	};
}

