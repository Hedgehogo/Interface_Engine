#pragma once
#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "../event.hpp"

namespace sf::Wheel {
	extern int value;
}

namespace ui {
	class WheelEvent : public Event {
	protected:
		bool active;
		
		void copy(WheelEvent* wheelEvent);
	
	public:
		explicit WheelEvent();
		
		virtual ~WheelEvent() = default;
		
		virtual void update(sf::Vector2i mousePosition, int value) = 0;
		
		virtual WheelEvent* copy() = 0;
	};
}
