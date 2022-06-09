#pragma once
#include "../iInteraction.h"

namespace ui {
	class DoubleInteraction : public virtual IInteraction {
	protected:
		IInteraction* first;
		IInteraction* second;
		
	public:
		DoubleInteraction(IInteraction* first, IInteraction* second);
		void setFirst(IInteraction* first);
		void setSecond(IInteraction* second);
		IInteraction* getFirst();
		IInteraction* getSecond();
		void start(sf::Vector2i mousePosition) override;
		bool update(sf::Vector2i mousePosition) override;
		void finish(sf::Vector2i mousePosition) override;
	};
}
