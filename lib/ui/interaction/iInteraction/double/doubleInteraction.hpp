#pragma once

#include "../iInteraction.hpp"

namespace ui {
	class DoubleInteraction : public virtual IInteraction {
	public:
		DoubleInteraction(BoxPtr<IInteraction>&& first, BoxPtr<IInteraction>&& second);
		
		void setFirst(BoxPtr<IInteraction>&& first);
		
		void setSecond(BoxPtr<IInteraction>&& second);
		
		IInteraction& getFirst();
		
		const IInteraction& getFirst() const;
		
		IInteraction& getSecond();
		
		const IInteraction& getSecond() const;
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		DoubleInteraction* copy() override;
	
	protected:
		BoxPtr<IInteraction> first;
		BoxPtr<IInteraction> second;
	};
}
