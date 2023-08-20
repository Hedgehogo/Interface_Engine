#pragma once

#include "../IInteraction.hpp"

namespace ui {
	class IBlockInteraction : public virtual IInteraction {
	public:
		IBlockInteraction();
		
		bool isBlocked() const override;
	};
}
