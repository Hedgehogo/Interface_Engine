#pragma once

#include "../IInteraction.hpp"

namespace ie {
	template<typename T = std::monostate>
	class IBasicBlockInteraction : public virtual IBasicInteraction<T> {
	public:
		struct Make : public IBasicInteraction<T>::Make {
			IBasicBlockInteraction<T>* make(BasicActionInitInfo<T> initInfo) override = 0;
		};
		
		bool isBlocked() const override;
	};
	
	using IBlockInteraction = IBasicBlockInteraction<>;
}

#include "IBasicBlockInteraction.inl"
