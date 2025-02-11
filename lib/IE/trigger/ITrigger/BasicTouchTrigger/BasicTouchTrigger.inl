namespace ie {
	namespace make_system {
		template<typename A_>
		BasicTouchTrigger<A_>::BasicTouchTrigger(BoxPtr<IBasicTouchAction<A_> >&& action, Key key) :
			action(std::move(action)), key(key) {
		}
		
		template<typename A_>
		auto BasicTouchTrigger<A_>::make(BasicActionInitInfo<A_> init_info) -> ie::BasicTouchTrigger<A_>* {
			return new ie::BasicTouchTrigger<A_>{std::move(*this), init_info};
		}
	}
	
	template<typename A_>
	BasicTouchTrigger<A_>::BasicTouchTrigger(Make&& make, BasicActionInitInfo<A_> init_info) :
		event_handler_(&init_info.event_handler), action_(make.action->make(init_info)), key_(make.key) {
	}
	
	template<typename A_>
	auto BasicTouchTrigger<A_>::get_key() -> Key {
		return key_;
	}
	
	template<typename A_>
	auto BasicTouchTrigger<A_>::get_action() -> IBasicTouchAction<A_>& {
		return *action_;
	}
	
	template<typename A_>
	auto BasicTouchTrigger<A_>::get_action() const -> IBasicTouchAction<A_> const& {
		return *action_;
	}
	
	template<typename A_>
	auto BasicTouchTrigger<A_>::set_action(BoxPtr<IBasicTouchAction<A_> >&& action) -> void {
		this->action_ = std::move(action);
	}
	
	template<typename A_>
	auto BasicTouchTrigger<A_>::start() -> void {
		action_->start();
	}
	
	template<typename A_>
	auto BasicTouchTrigger<A_>::handle_event(Event event) -> bool {
		return tracker_.collect(*event_handler_, event);
	}
	
	template<typename A_>
	auto BasicTouchTrigger<A_>::update() -> void {
		action_->update(tracker_.reset().map(Touch::from(event_handler_->get_key(key_))));
	}
	
	template<typename A_>
	auto BasicTouchTrigger<A_>::finish() -> void {
		action_->finish();
	}
}

template<typename A_>
auto ieml::Decode<char, ie::make_system::BasicTouchTrigger<A_> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::make_system::BasicTouchTrigger<A_> > {
	auto& clear_node{node.get_clear()};
	return ie::make_system::BasicTouchTrigger<A_>{
		clear_node.at("action").except().template as<bp::BoxPtr<ie::make_system::IBasicTouchAction<A_> > >().except(),
		clear_node.get_as<ie::Key>("key").except().ok_or(ie::Key::MouseLeft),
	};
}
