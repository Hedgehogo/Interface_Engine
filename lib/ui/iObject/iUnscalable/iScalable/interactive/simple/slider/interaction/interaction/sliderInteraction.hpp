#pragma once

#include "../../../../../../../../interaction/iInteraction/oneKey/oneKeyInteraction.hpp"
#include "../../../../../../../../interaction/iInteraction/block/pressed/pressedInteraction.hpp"
#include "../slideEvent/sliderEvent.hpp"
#include "../wheelEvent/sliderWheelEvent.hpp"

namespace ui {
	class SliderInteraction : public OneKeyInteraction {
	public:
		SliderInteraction(BaseSlider& slider, Key key, bool wheelHorizontal = false, SliderWheelEvent::Relativity wheelRelativity = SliderWheelEvent::Relativity::relationSlider, sf::Vector2f wheelSensitivity = {0.2f, 0.2f});
		
		SliderInteraction(BaseSlider& slider, Key key, sf::Vector2i division = {10, 10}, bool wheelHorizontal = false);
		
		SliderInteraction(const SliderInteraction& other);
		
		void init(InteractionInitInfo interactionInitInfo) override;
		
		void setSlider(BaseSlider& slider);
		
		void update(sf::Vector2i mousePosition) override;
		
		SliderInteraction* copy() override;
	
	protected:
		PressedInteraction slideInteraction;
		SliderWheelEvent wheelEvent;
	};
}
