#pragma once
#include <SFML/Graphics.hpp>

namespace sf::Wheel {
	extern int value;
}

namespace ui {
	class WheelEvent {
	protected:
		bool active;
	
	public:
		explicit WheelEvent();
		
		virtual ~WheelEvent() = default;
		
		virtual void update(sf::Vector2i mousePosition, int value) = 0;
	};
}
