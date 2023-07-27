#pragma once

#include "../../../../../../../../interaction/event/key/simple/keyEventSimple.hpp"

namespace ui {
	class BaseSlider;
	
	class SliderEvent : public KeyEvent_Simple {
	protected:
		sf::Vector2f getMousePosition();
		
		void copy(SliderEvent* sliderEvent);
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		explicit SliderEvent(BaseSlider& slider, sf::Vector2i division = {0, 0});
		
		void setSlider(BaseSlider& slider);
		
		SliderEvent* copy() override;
	
	protected:
		BaseSlider* slider;
		sf::Vector2i startMousePosition;
		sf::Vector2f startValue;
		sf::Vector2i division;
	};
}
