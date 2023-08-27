#pragma once

#include "../../../Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "../IEvent.hpp"
#include "../../../SfmlEvents/MouseWheel/MouseWheel.hpp"

namespace ui {
	class WheelEvent : public IEvent {
	public:
		explicit WheelEvent();
		
		virtual void update(sf::Vector2i mousePosition, int value) = 0;
		
		virtual WheelEvent* copy() = 0;
	
	protected:
		bool active;
	};
}
