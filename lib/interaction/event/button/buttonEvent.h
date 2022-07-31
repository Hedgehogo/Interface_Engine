#pragma once
#include <SFML/Graphics.hpp>

namespace ui {
	class ButtonEvent {
	protected:
		bool pressed;
		
		void copy(ButtonEvent* buttonEvent);
		
	public:
		explicit ButtonEvent();
		
		virtual ~ButtonEvent() = default;
		
		virtual void setPressed(bool pressed);
		
		virtual void update(sf::Vector2i mousePosition, bool press) = 0;
		
		virtual ButtonEvent* copy() = 0;
	};
}
