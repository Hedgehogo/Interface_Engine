namespace ie {
	namespace detail {
		namespace make_system {
			template<typename A_>
			BasicHotkeyTriggerHotkey<A_>::BasicHotkeyTriggerHotkey(
				bp::BoxPtr<make_system::BasicKeysTrigger<A_> >&& trigger,
				size_t state
			) : trigger(std::move(trigger)), state(state) {
			}
			
			template<typename A_>
			auto BasicHotkeyTriggerHotkey<A_>::make(BasicActionInitInfo<A_> init_info) -> detail::BasicHotkeyTriggerHotkey<A_>* {
				return new detail::BasicHotkeyTriggerHotkey<A_>{std::move(*this), init_info};
			}
		}
		
		template<typename A_>
		BasicHotkeyTriggerHotkey<A_>::BasicHotkeyTriggerHotkey(Make&& make, BasicActionInitInfo<A_> init_info) :
			trigger_(make.trigger->make(init_info)), state_(make.state) {
		}
		
		template<typename A_>
		BasicHotkeyTriggerHotkey<A_>::BasicHotkeyTriggerHotkey(bp::BoxPtr<BasicKeysTrigger<A_> >&& trigger, size_t state) :
			trigger_(std::move(trigger)), state_(state) {
		}
		
		template<typename A_>
		BasicHotkeyTriggerHotkey<A_>::BasicHotkeyTriggerHotkey(size_t state) :
			trigger_(nullptr), state_(state) {
		}
	}
	
	namespace make_system {
		template<typename A_>
		BasicHotkeyTrigger<A_>::BasicHotkeyTrigger(std::vector<std::vector<Hotkey> > hotkeys, size_t state) :
			hotkeys(std::move(hotkeys)), state(state) {
		}
		
		template<typename A_>
		auto BasicHotkeyTrigger<A_>::make(BasicActionInitInfo<A_> init_info) -> ie::BasicHotkeyTrigger<A_>* {
			return new ie::BasicHotkeyTrigger<A_>{std::move(*this), init_info};
		}
	}
	
	template<typename A_>
	BasicHotkeyTrigger<A_>::BasicHotkeyTrigger(Make&& make, BasicActionInitInfo<A_> init_info) :
		hotkey_states_(map_make(std::move(make.hotkeys), init_info)), now_hotkeys_(&hotkey_states_[make.state]) {
	}
	
	template<typename A_>
	auto BasicHotkeyTrigger<A_>::set_hotkey_action(size_t state, Hotkey* hotkey_action) -> void {
		if(hotkey_states_.size() <= state) {
			hotkey_states_.resize(state, {});
		}
		hotkey_states_[state].emplace_back(hotkey_action);
	}
	
	template<typename A_>
	auto BasicHotkeyTrigger<A_>::get_hotkeys(int state) -> std::vector<Hotkey> {
		return hotkey_states_[state];
	}
	
	template<typename A_>
	auto BasicHotkeyTrigger<A_>::get_hotkey(int state, int i) -> Hotkey {
		return hotkey_states_[state][i];
	}
	
	template<typename A_>
	auto BasicHotkeyTrigger<A_>::start() -> void {
		for(auto& hotkey: *now_hotkeys_) {
			hotkey.trigger_->start();
		}
	}
	
	template<typename A_>
	auto BasicHotkeyTrigger<A_>::handle_event(Event event) -> bool {
		/*old_action*/
		return false;
	}
	
	template<typename A_>
	auto BasicHotkeyTrigger<A_>::update() -> void {
		for(auto& hotkey: *now_hotkeys_) {
			hotkey.trigger_->update();
			if(hotkey.trigger_->is_press() && hotkey.state_ != std::numeric_limits<size_t>::max()) {
				finish();
				now_hotkeys_ = &hotkey_states_[hotkey.state_];
				start();
			}
		}
	}
	
	template<typename A_>
	auto BasicHotkeyTrigger<A_>::finish() -> void {
		for(auto& hotkey: *now_hotkeys_) {
			hotkey.trigger_->finish();
		}
	}
}

template<typename A_>
auto ieml::Decode<char, ie::detail::make_system::BasicHotkeyTriggerHotkey<A_> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::detail::make_system::BasicHotkeyTriggerHotkey<A_> > {
	auto map{node.get_map_view().except()};
	return ie::detail::make_system::BasicHotkeyTriggerHotkey<A_>{
		map.at("trigger").except().as<bp::BoxPtr<ie::make_system::BasicKeysTrigger<A_> > >().except(),
		map.get_as<size_t>("state").except().ok_or(std::numeric_limits<size_t>::max())
	};
}

template<typename A_>
auto ieml::Decode<char, ie::make_system::BasicHotkeyTrigger<A_> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::make_system::BasicHotkeyTrigger<A_> > {
	auto map{node.get_map_view().except()};
	return ie::make_system::BasicHotkeyTrigger<A_>{
		map.at("hotkeys").except().as<std::vector<std::vector<ie::detail::make_system::BasicHotkeyTriggerHotkey<A_> > > >().except(),
		map.get_as<size_t>("state").except().ok_or(0)
	};
}

