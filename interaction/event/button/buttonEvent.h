#pragma once
#include <SFML/Graphics.hpp>

namespace ui {
	class ButtonEvent {
	protected:
		bool pressed;
	public:
		explicit ButtonEvent();
		
		virtual ~ButtonEvent() = default;
		
		virtual void update(sf::Vector2i mousePosition, bool press) = 0;
	};
}
