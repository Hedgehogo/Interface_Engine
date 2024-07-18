//included into BasicActiveInteraction.hpp

namespace ie {
	namespace make_system {
		template<typename A_>
		BasicActiveInteraction<A_>::BasicActiveInteraction(BoxPtr<IBasicInteraction<A_> >&& interaction) :
			interaction(std::move(interaction)) {
		}
		
		template<typename A_>
		auto BasicActiveInteraction<A_>::make(BasicActionInitInfo<A_> init_info) -> ie::BasicActiveInteraction<A_>* {
			return new ie::BasicActiveInteraction<A_>{std::move(*this), init_info};
		}
	}
	
	template<typename A_>
	BasicActiveInteraction<A_>::BasicActiveInteraction(Make&& make, BasicActionInitInfo<A_> init_info) :
		interaction_(make.interaction->make(init_info)), interaction_manager_(&init_info.interaction_manager), prioritised_(false), active_(false) {
	}
	
	template<typename A_>
	auto BasicActiveInteraction<A_>::start() -> void {
	}
	
	template<typename A_>
	auto BasicActiveInteraction<A_>::handle_event(Event event) -> bool {
		if(!prioritised_ && interaction_->handle_event(event)) {
			active_ = true;
			return true;
		}
		return false;
	}
	
	template<typename A_>
	auto BasicActiveInteraction<A_>::handle_event_prioritised(Event event) -> bool {
		if(prioritised_ && interaction_->handle_event(event)) {
			active_ = true;
			return true;
		}
		return false;
	}
	
	template<typename A_>
	auto BasicActiveInteraction<A_>::update() -> void {
		if(prioritised_ != active_) {
			prioritised_ = active_;
			if(prioritised_) {
				interaction_manager_->add_prioritised(*this);
			} else {
				interaction_manager_->delete_prioritised(*this);
			}
		}
		interaction_->update();
	}
	
	template<typename A_>
	auto BasicActiveInteraction<A_>::finish() -> void {
	}
}

template<typename A_>
auto ieml::Decode<char, ie::make_system::BasicActiveInteraction<A_> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::make_system::BasicActiveInteraction<A_> > {
	using Action = bp::BoxPtr<ie::make_system::IBasicActivityAction<A_> >;
	return ie::make_system::BasicActiveInteraction<A_>{
		node.template as<Action>().ok_or_else([&node] {
			return node.get_clear().at("interaction").except().template as<Action>().except();
		})
	};
}
