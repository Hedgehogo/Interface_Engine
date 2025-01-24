#pragma once

#include "../../TriggerManager/TriggerManager.hpp"
#include "../IBasicPrioritisedTrigger/IBasicPrioritisedTrigger.hpp"

namespace ie {
	template<typename A_>
	class BasicActiveTrigger;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct BasicActiveTrigger : public virtual IBasicPrioritisedTrigger<A_> {
			BoxPtr<IBasicTrigger<A_> > trigger;
			
			BasicActiveTrigger(BoxPtr<IBasicTrigger<A_> >&& trigger);
			
			auto make(BasicActionInitInfo<A_> init_info) -> ie::BasicActiveTrigger<A_>* override;
		};
	}
	
	template<typename A_ = std::monostate>
	class BasicActiveTrigger : public virtual IBasicPrioritisedTrigger<A_> {
	public:
		using Make = make_system::BasicActiveTrigger<A_>;
		
		BasicActiveTrigger(Make&& make, BasicActionInitInfo<A_> init_info);
		
		auto start() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto handle_event_prioritised(Event event) -> bool override;
		
		auto update() -> void override;
		
		auto finish() -> void override;
		
	private:
		BoxPtr<IBasicTrigger<A_> > trigger_;
		TriggerManager* trigger_manager_;
		bool prioritised_;
		bool active_;
	};
	
	using ActiveTrigger = BasicActiveTrigger<>;
}

template<typename A_>
struct ieml::Decode<char, ie::make_system::BasicActiveTrigger<A_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicActiveTrigger<A_> >;
};

#include "BasicActiveTrigger.inl"
