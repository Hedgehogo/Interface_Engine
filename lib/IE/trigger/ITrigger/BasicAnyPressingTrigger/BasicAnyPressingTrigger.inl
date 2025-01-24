//included into BasicAnyPressingTrigger.hpp

namespace ie {
	namespace make_system {
		template<typename A_>
		BasicAnyPressingTrigger<A_>::BasicAnyPressingTrigger(BoxPtr<IBasicActivityAction<A_> >&& action, Key key) :
			action(std::move(action)), key(key) {
		}
		
		template<typename A_>
		auto BasicAnyPressingTrigger<A_>::make(BasicActionInitInfo<A_> init_info) -> ie::BasicAnyPressingTrigger<A_>* {
			return new ie::BasicAnyPressingTrigger<A_>{std::move(*this), init_info};
		}
	}
	
	template<typename A_>
	BasicAnyPressingTrigger<A_>::BasicAnyPressingTrigger(Make&& make, BasicActionInitInfo<A_> init_info) :
		event_handler_(&init_info.event_handler), action_(make.action->make(init_info)), key_(make.key) {
	}
	
	template<typename A_>
	auto BasicAnyPressingTrigger<A_>::start() -> void {
		action_->start();
	}
	
	template<typename A_>
	auto BasicAnyPressingTrigger<A_>::handle_event(Event event) -> bool {
		return false;
	}
	
	template<typename A_>
	auto BasicAnyPressingTrigger<A_>::update() -> void {
		action_->update(event_handler_->get_key(key_));
	}
	
	template<typename A_>
	auto BasicAnyPressingTrigger<A_>::finish() -> void {
		action_->finish();
	}
}

template<typename A_>
auto ieml::Decode<char, ie::make_system::BasicAnyPressingTrigger<A_> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::make_system::BasicAnyPressingTrigger<A_> > {
	auto& clear_node{node.get_clear()};
	return ie::make_system::BasicAnyPressingTrigger<A_>{
		clear_node.at("action").except().template as<bp::BoxPtr<ie::make_system::IBasicActivityAction<A_> > >().except(),
		clear_node.get_as<ie::Key>("key").except().ok_or(ie::Key::MouseLeft),
	};
}
