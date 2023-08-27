#pragma once

#include "../IInteraction.hpp"

namespace ie {
	template<typename T = std::monostate>
	class IBasicBlockInteraction : public virtual IBasicInteraction<T> {
	public:
		bool isBlocked() const override;
	};
	
	using IBlockInteraction = IBasicBlockInteraction<>;
}

#include "IBasicBlockInteraction.inl"
