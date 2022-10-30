#include "sliderInteraction.hpp"
#include <utility>

namespace ui {
	SliderInteraction::SliderInteraction(BaseSlider &slider, Key button, bool wheelHorizontal, SliderWheelEvent::Relativity wheelRelativity, sf::Vector2f wheelSensitivity) :
		slideInteraction(new SliderEvent{slider, {0, 0}}, button),
		OneButtonInteraction(new AddInteractionEvent{slideInteraction}, button),
		wheelEvent(slider, wheelHorizontal, wheelRelativity, wheelSensitivity) {
	}
	
	SliderInteraction::SliderInteraction(BaseSlider &slider, Key button, sf::Vector2i division, bool wheelHorizontal) :
		slideInteraction(new SliderEvent{slider, division}, button),
		OneButtonInteraction(new AddInteractionEvent{slideInteraction}, button),
		wheelEvent(slider, wheelHorizontal, SliderWheelEvent::Relativity::relationArea, {1.0f / static_cast<float>(division.x), 1.0f / static_cast<float>(division.y)}) {
	}
	
	void SliderInteraction::init(InteractionManager &interactionManager) {
		slideInteraction.init(interactionManager);
		dynamic_cast<AddInteractionEvent *>(event)->init(interactionManager);
	}
	
	void SliderInteraction::setSlider(BaseSlider &slider) {
		dynamic_cast<SliderEvent *>(slideInteraction.getEvent())->setSlider(slider);
		wheelEvent.setSlider(slider);
	}
	
	void SliderInteraction::update(sf::Vector2i mousePosition) {
		wheelEvent.update(mousePosition, sf::Wheel::value);
		return OneButtonInteraction::update(mousePosition);
	}
	
	SliderInteraction::SliderInteraction(SliderWheelEvent wheelEvent, PressedInteraction slideInteraction) :
		OneButtonInteraction(nullptr, slideInteraction.getButton()),
		wheelEvent(std::move(wheelEvent)),
		slideInteraction(slideInteraction) {
		event = new AddInteractionEvent{this->slideInteraction};
	}
	
	SliderInteraction *SliderInteraction::copy() {
		return new SliderInteraction{wheelEvent, slideInteraction};
	}
}
