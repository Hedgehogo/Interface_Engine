#pragma once

#include <SFML/System/Vector2.hpp>

namespace ui {
	class KeyEvent {
	protected:
		bool pressed;
		
		void copy(KeyEvent* keyEvent);
		
	public:
		explicit KeyEvent();
		
		virtual ~KeyEvent() = default;
		
		virtual void setPressed(bool pressed);

		virtual void update(sf::Vector2i mousePosition, bool press) = 0;

		virtual KeyEvent* copy() = 0;
	};
}
