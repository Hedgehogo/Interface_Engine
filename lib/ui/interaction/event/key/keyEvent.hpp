#pragma once

#include <SFML/System/Vector2.hpp>
#include "../iEvent.hpp"

namespace ui {
	class KeyEvent : public IEvent {
	protected:
		bool pressed;
		
		void copy(KeyEvent* keyEvent);
	
	public:
		explicit KeyEvent();
		
		virtual void setPressed(bool pressed);
		
		virtual void update(sf::Vector2i mousePosition, bool press) = 0;
		
		virtual KeyEvent* copy() = 0;
	};
}
