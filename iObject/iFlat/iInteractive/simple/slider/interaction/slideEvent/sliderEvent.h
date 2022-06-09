#pragma once

#include "../../../../../../../interaction/event/button/simple/buttonEventSimple.h"

namespace ui {
	class BaseSlider;
	class SliderEvent : public ButtonEvent_Simple {
	protected:
		BaseSlider& slider;
		sf::Vector2i startMousePosition;
		sf::Vector2f startValue;
		sf::Vector2i division;
		
		void startPressed(sf::Vector2i windowPosition) override;
		
		void stopPressed (sf::Vector2i windowPosition) override;
		
		void whilePressed(sf::Vector2i windowPosition) override;
		
		void notPressed  (sf::Vector2i windowPosition) override;
		
	public:
		SliderEvent(BaseSlider &slider, sf::Vector2i division = {0, 0});
	};
}
