#pragma once

#include "../IInteraction.hpp"

namespace ie {
	template<typename T>
	class IBasicBlockInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct IBasicBlockInteraction : public virtual IBasicInteraction<T> {
			auto make(BasicActionInitInfo<T> init_info) -> ie::IBasicBlockInteraction<T>* override = 0;
		};
	}
	
	template<typename T = std::monostate>
	class IBasicBlockInteraction : public virtual IBasicInteraction<T> {
	public:
		using Make = make_system::IBasicBlockInteraction<T>;
		
		auto is_blocked() const -> bool override;
	};
	
	using IBlockInteraction = IBasicBlockInteraction<>;
}

#include "IBasicBlockInteraction.inl"
