#pragma once

#include "../iInteraction.hpp"

namespace ui {
	class DoubleInteraction : public virtual IInteraction {
	public:
		DoubleInteraction(IInteraction* first, IInteraction* second);
		
		~DoubleInteraction() override;
		
		void setFirst(IInteraction* first);
		
		void setSecond(IInteraction* second);
		
		IInteraction* getFirst();
		
		IInteraction* getSecond();
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		DoubleInteraction* copy() override;
	
	protected:
		IInteraction* first;
		IInteraction* second;
	};
}
