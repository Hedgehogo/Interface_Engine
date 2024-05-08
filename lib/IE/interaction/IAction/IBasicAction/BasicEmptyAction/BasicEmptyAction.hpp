#pragma once

#include "../IBasicAction.hpp"

namespace ie {
	template<typename A_>
	class BasicEmptyAction;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct BasicEmptyAction : public virtual IBasicAction<A_> {
			auto make(BasicActionInitInfo<A_> init_info) -> ie::BasicEmptyAction<A_>* override;
		};
	}
	
	template<typename A_ = std::monostate>
	class BasicEmptyAction : public virtual IBasicAction<A_> {
	public:
		using Make = make_system::BasicEmptyAction<A_>;
		
		BasicEmptyAction(Make&& make, BasicActionInitInfo<A_> init_info);
		
		BasicEmptyAction() = default;
		
		auto update(bool active) -> void override;
	};
	
	using EmptyAction = BasicEmptyAction<>;
}

#include "BasicEmptyAction.inl"
