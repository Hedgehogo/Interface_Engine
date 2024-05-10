//included into BasicAnyPressingInteraction.hpp

namespace ie {
	namespace make_system {
		template<typename A_>
		BasicAnyPressingInteraction<A_>::BasicAnyPressingInteraction(BoxPtr<IBasicActivityAction<A_> >&& action, Key key) :
			action(std::move(action)), key(key) {
		}
		
		template<typename A_>
		auto BasicAnyPressingInteraction<A_>::make(BasicActionInitInfo<A_> init_info) -> ie::BasicAnyPressingInteraction<A_>* {
			return new ie::BasicAnyPressingInteraction<A_>{std::move(*this), init_info};
		}
	}
	
	template<typename A_>
	BasicAnyPressingInteraction<A_>::BasicAnyPressingInteraction(Make&& make, BasicActionInitInfo<A_> init_info) :
		event_handler_(&init_info.event_handler), action_(make.action->make(init_info)), key_(make.key) {
	}
	
	template<typename A_>
	auto BasicAnyPressingInteraction<A_>::start(sf::Vector2i) -> void {
		action_->start();
	}
	
	template<typename A_>
	auto BasicAnyPressingInteraction<A_>::update(sf::Vector2i mouse_position) -> void {
		action_->update(event_handler_->get_key(key_));
	}
	
	template<typename A_>
	auto BasicAnyPressingInteraction<A_>::finish(sf::Vector2i) -> void {
		action_->finish();
	}
}

template<typename A_>
auto ieml::Decode<char, ie::make_system::BasicAnyPressingInteraction<A_> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::make_system::BasicAnyPressingInteraction<A_> > {
	auto& clear_node{node.get_clear()};
	return ie::make_system::BasicTouchInteraction<A_>{
		clear_node.at("action").except().template as<bp::BoxPtr<ie::make_system::IBasicActivityAction<A_> > >().except(),
		clear_node.get_as<ie::Key>("key").except().ok_or(ie::Key::MouseLeft),
	};
}
