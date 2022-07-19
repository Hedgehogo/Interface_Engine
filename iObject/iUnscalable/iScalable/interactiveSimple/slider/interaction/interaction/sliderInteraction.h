#pragma once
#include "../../../../../../../interaction/iInteraction/oneButton/oneButtonInteraction.h"
#include "../../../../../../../interaction/iInteraction/block/pressed/pressedInteraction.h"
#include "../../../../../../../interaction/event/button/addInteraction/addInteractionEvent.h"
#include "../slideEvent/sliderEvent.h"
#include "../wheelEvent/sliderWheelEvent.h"

namespace ui {
	class SliderInteraction : public OneButtonInteraction {
	protected:
		SliderWheelEvent wheelEvent;
		PressedInteraction slideInteraction;
		
		SliderInteraction(SliderWheelEvent wheelEvent, PressedInteraction slideInteraction);
	
	public:
		SliderInteraction(BaseSlider &slider, sf::Mouse::Button button, bool wheelHorizontal = false, SliderWheelEvent::Sensitivity wheelRelativity = SliderWheelEvent::Sensitivity::relationSlider, sf::Vector2f wheelSensitivity = {0.2f, 0.2f});
		
		SliderInteraction(BaseSlider &slider, sf::Mouse::Button button, sf::Vector2i division = {10, 10}, bool wheelHorizontal = false);
		
		void init(InteractionManager &interactionManager);
		
		void setSlider(BaseSlider &slider);
		
		bool update(sf::Vector2i mousePosition) override;
		
		SliderInteraction* copy() override;
	};
}
