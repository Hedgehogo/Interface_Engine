#pragma once

#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "../iEvent.hpp"
#include "../../../sfmlEvents/mouseWheel/mouseWheel.hpp"

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
