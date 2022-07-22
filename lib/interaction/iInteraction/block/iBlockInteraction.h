#pragma once
#include "../iInteraction.h"

namespace ui {
	class IBlockInteraction : public virtual IInteraction {
	public:
		bool update(sf::Vector2i mousePosition) override;
	};
}
