#pragma once

#include "../../../../../../../../interaction/event/button/simple/buttonEventSimple.h"

namespace ui {
	class BaseSlider;
	class SliderEvent : public ButtonEvent_Simple {
	protected:
		BaseSlider* slider;
		sf::Vector2i startMousePosition;
		sf::Vector2f startValue;
		sf::Vector2i division;
		
		void copy(SliderEvent* sliderEvent);
		
		void startPressed(sf::Vector2i mousePosition) override;
		
		void stopPressed (sf::Vector2i mousePosition) override;
		
		void whilePressed(sf::Vector2i mousePosition) override;
		
		void whileNotPressed  (sf::Vector2i mousePosition) override;
		
	public:
		explicit SliderEvent(BaseSlider &slider, sf::Vector2i division = {0, 0});
		
		void setSlider(BaseSlider& slider);
		
		SliderEvent* copy() override;
	};
}
