#pragma once
#include "../../../../../../../interaction/event/wheel/simple/wheelEventSimple.h"

namespace ui {
	class BaseSlider;
	class SliderWheelEvent : public WheelEvent_Simple {
	public:
		enum class Sensitivity {
			relationArea,
			relationSlider
		};
	protected:
		BaseSlider* slider;
		sf::Vector2f sensitivity;
		bool horizontal;
		bool relativity;
		
		void startPressed(sf::Vector2i windowPosition, int value) override;
		
		void stopPressed(sf::Vector2i windowPosition, int value) override;
		
		void whilePressed(sf::Vector2i windowPosition, int value) override;
		
		void notPressed(sf::Vector2i windowPosition, int value) override;
		
	public:
		explicit SliderWheelEvent(BaseSlider &slider, bool horizontal = false, Sensitivity relativity = Sensitivity::relationSlider, sf::Vector2f sensitivity = {0.2f, 0.2f});
		
		void setSlider(BaseSlider& slider);
		
		SliderWheelEvent* copy() override;
	};
}
