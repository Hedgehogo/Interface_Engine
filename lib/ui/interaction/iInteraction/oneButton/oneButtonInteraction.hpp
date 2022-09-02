#pragma once
#include "../iInteraction.hpp"

namespace ui {
	class OneButtonInteraction : public virtual IInteraction {
	protected:
		ButtonEvent *event;
		sf::Mouse::Button button;
	
	public:
		OneButtonInteraction(ButtonEvent *event, sf::Mouse::Button button);
		
		~OneButtonInteraction() override;
		
		sf::Mouse::Button getButton();
		
		ButtonEvent* getEvent();
		
		void setEvent(ButtonEvent *event);
		
		void start(sf::Vector2i mousePosition) override;
		
		bool update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		OneButtonInteraction* copy() override;
	};
}
