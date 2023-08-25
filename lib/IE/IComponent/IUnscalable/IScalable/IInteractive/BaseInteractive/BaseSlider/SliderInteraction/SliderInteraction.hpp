#pragma once

#include "IE/Interaction/IInteraction/BasicOneKeyInteraction/BasicOneKeyInteraction.hpp"
#include "IE/Interaction/IInteraction/BasicPressedInteraction/BasicPressedInteraction.hpp"
#include "../SliderEvent/SliderEvent.hpp"
#include "../SliderWheelEvent/SliderWheelEvent.hpp"

namespace ui {
	class SliderInteraction : public OneKeyInteraction {
	public:
		SliderInteraction(BaseSlider& slider, Key key, bool wheelHorizontal = false, SliderWheelEvent::Relativity wheelRelativity = SliderWheelEvent::Relativity::relationSlider, sf::Vector2f wheelSensitivity = {0.2f, 0.2f});
		
		SliderInteraction(BaseSlider& slider, Key key, sf::Vector2i division = {10, 10}, bool wheelHorizontal = false);
		
		SliderInteraction(BaseSlider& slider, Key key, sf::Vector2i division, bool wheelHorizontal, SliderWheelEvent::Relativity wheelRelativity, sf::Vector2f wheelSensitivity);
		
		SliderInteraction(const SliderInteraction& other);
		
		void init(InteractionInitInfo interactionInitInfo) override;
		
		void setSlider(BaseSlider& slider);
		
		void update(sf::Vector2i mousePosition) override;
		
		SliderInteraction* copy() override;
	
	protected:
		SliderWheelEvent wheelEvent;
		PressedInteraction slideInteraction;
	};
}
