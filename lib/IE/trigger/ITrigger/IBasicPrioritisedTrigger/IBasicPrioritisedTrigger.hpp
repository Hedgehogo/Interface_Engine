#pragma once

#include "../IPrioritisedTrigger/IPrioritisedTrigger.hpp"

namespace ie {
	template<typename A_>
	class IBasicPrioritisedTrigger;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct IBasicPrioritisedTrigger : public virtual IBasicTrigger<A_> {
			auto make(BasicActionInitInfo<A_> init_info) -> ie::IBasicPrioritisedTrigger<A_>* override = 0;
		};
	}
	
	template<typename A_ = std::monostate>
	class IBasicPrioritisedTrigger : public virtual IBasicTrigger<A_>, public virtual IPrioritisedTrigger {
	public:
		using Make = make_system::IBasicPrioritisedTrigger<A_>;
	};
}
