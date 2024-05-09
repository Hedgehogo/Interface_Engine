#pragma once

#include "../IInteraction.hpp"

namespace ie {
	template<typename A_>
	class IBasicPrioritisedInteraction;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct IBasicPrioritisedInteraction : public virtual IBasicInteraction<A_> {
			auto make(BasicActionInitInfo<A_> init_info) -> ie::IBasicPrioritisedInteraction<A_>* override = 0;
		};
	}
	
	template<typename A_ = std::monostate>
	class IBasicPrioritisedInteraction : public virtual IBasicInteraction<A_> {
	public:
		using Make = make_system::IBasicPrioritisedInteraction<A_>;
		
		auto is_blocked() const -> bool override;
		
		/*old_action
		virtual auto handle_event_prioritised(Event event) -> bool;
		*/
	};
	
	using IPrioritisedInteraction = IBasicPrioritisedInteraction<>;
}

#include "IBasicPrioritisedInteraction.inl"
