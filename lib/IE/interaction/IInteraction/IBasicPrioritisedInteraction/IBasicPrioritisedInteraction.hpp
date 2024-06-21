#pragma once

#include "../IPrioritisedInteraction/IPrioritisedInteraction.hpp"

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
	class IBasicPrioritisedInteraction : public virtual IBasicInteraction<A_>, public virtual IPrioritisedInteraction {
	public:
		using Make = make_system::IBasicPrioritisedInteraction<A_>;
	};
}
