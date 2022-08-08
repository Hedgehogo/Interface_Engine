#pragma once
#include "../iInteraction.h"

namespace ui {
	class EmptyInteraction : public virtual IInteraction {
	public:
		void start(sf::Vector2i mousePosition) override;
		
		bool update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		EmptyInteraction* copy() override;
	};
}
