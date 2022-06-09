#pragma once
#include "../iInteraction.h"

namespace ui {
	class OneButtonInteraction : public virtual IInteraction {
	protected:
		ButtonEvent *event;
		sf::Mouse::Button button;
	
	public:
		OneButtonInteraction(ButtonEvent *event, sf::Mouse::Button button);
		
		~OneButtonInteraction() override;
		
		void start(sf::Vector2i mousePosition) override;
		
		bool update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
	};
}
