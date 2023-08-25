#pragma once

#include "../IInteraction.hpp"

namespace ui {
	template<typename T = std::monostate>
	class IBasicBlockInteraction : public virtual IBasicInteraction<T> {
	public:
		bool isBlocked() const override;
	};
	
	using IBlockInteraction = IBasicBlockInteraction<>;
}

#include "IBasicBlockInteraction.inl"
