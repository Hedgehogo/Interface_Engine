//included into BasicActiveTrigger.hpp

namespace ie {
	namespace make_system {
		template<typename A_>
		BasicActiveTrigger<A_>::BasicActiveTrigger(BoxPtr<IBasicTrigger<A_> >&& trigger) :
			trigger(std::move(trigger)) {
		}
		
		template<typename A_>
		auto BasicActiveTrigger<A_>::make(BasicActionInitInfo<A_> init_info) -> ie::BasicActiveTrigger<A_>* {
			return new ie::BasicActiveTrigger<A_>{std::move(*this), init_info};
		}
	}
	
	template<typename A_>
	BasicActiveTrigger<A_>::BasicActiveTrigger(Make&& make, BasicActionInitInfo<A_> init_info) :
		trigger_(make.trigger->make(init_info)), trigger_manager_(&init_info.trigger_manager), prioritised_(false), active_(false) {
	}
	
	template<typename A_>
	auto BasicActiveTrigger<A_>::start() -> void {
	}
	
	template<typename A_>
	auto BasicActiveTrigger<A_>::handle_event(Event event) -> bool {
		if(!prioritised_ && trigger_->handle_event(event)) {
			active_ = true;
			return true;
		}
		return false;
	}
	
	template<typename A_>
	auto BasicActiveTrigger<A_>::handle_event_prioritised(Event event) -> bool {
		if(prioritised_ && trigger_->handle_event(event)) {
			active_ = true;
			return true;
		}
		return false;
	}
	
	template<typename A_>
	auto BasicActiveTrigger<A_>::update() -> void {
		if(prioritised_ != active_) {
			prioritised_ = active_;
			if(prioritised_) {
				trigger_manager_->add_prioritised(*this);
			} else {
				trigger_manager_->delete_prioritised(*this);
			}
		}
		trigger_->update();
	}
	
	template<typename A_>
	auto BasicActiveTrigger<A_>::finish() -> void {
	}
}

template<typename A_>
auto ieml::Decode<char, ie::make_system::BasicActiveTrigger<A_> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::make_system::BasicActiveTrigger<A_> > {
	using Action = bp::BoxPtr<ie::make_system::IBasicActivityAction<A_> >;
	return ie::make_system::BasicActiveTrigger<A_>{
		node.template as<Action>().ok_or_else([&node] {
			return node.get_clear().at("trigger").except().template as<Action>().except();
		})
	};
}
