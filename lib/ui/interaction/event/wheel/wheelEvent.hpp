#pragma once
#include <SFML/Graphics.hpp>
#include "../../../../yaml/yamlWithSfml/yamlBuilder/yamlBuilder.hpp"

namespace sf::Wheel {
	extern int value;
}

namespace ui {
	class WheelEvent {
	protected:
		bool active;
		
		void copy(WheelEvent* wheelEvent);
	
	public:
		explicit WheelEvent();
		
		virtual ~WheelEvent() = default;
		
		virtual void update(sf::Vector2i mousePosition, int value) = 0;
		
		virtual WheelEvent* copy() = 0;

        static WheelEvent* createFromYaml(const YAML::Node &node);
	};
}
