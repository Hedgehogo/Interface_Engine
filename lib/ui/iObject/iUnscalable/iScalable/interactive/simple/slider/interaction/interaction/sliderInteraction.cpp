#include "sliderInteraction.hpp"
#include "../../../../../../../../interaction/event/key/addInteraction/blockInteraction/addBlockInteractionEvent.hpp"
#include <utility>

namespace ui {
	SliderInteraction::SliderInteraction(BaseSlider &slider, Key key, bool wheelHorizontal, SliderWheelEvent::Relativity wheelRelativity, sf::Vector2f wheelSensitivity) :
		slideInteraction(new SliderEvent{slider, {0, 0}}, key),
		OneKeyInteraction(new AddBlockInteractionEvent{slideInteraction}, key),
		wheelEvent(slider, wheelHorizontal, wheelRelativity, wheelSensitivity) {
	}
	
	SliderInteraction::SliderInteraction(BaseSlider &slider, Key key, sf::Vector2i division, bool wheelHorizontal) :
		slideInteraction(new SliderEvent{slider, division}, key),
		OneKeyInteraction(new AddBlockInteractionEvent{slideInteraction}, key),
		wheelEvent(slider, wheelHorizontal, SliderWheelEvent::Relativity::relationArea, {1.0f / static_cast<float>(division.x), 1.0f / static_cast<float>(division.y)}) {
	}
	
	void SliderInteraction::init(InteractionManager &interactionManager) {
		slideInteraction.init(interactionManager);
		dynamic_cast<AddBlockInteractionEvent *>(event)->init(interactionManager);
	}
	
	void SliderInteraction::setSlider(BaseSlider &slider) {
		dynamic_cast<SliderEvent *>(slideInteraction.getEvent())->setSlider(slider);
		wheelEvent.setSlider(slider);
	}
	
	void SliderInteraction::update(sf::Vector2i mousePosition) {
		wheelEvent.update(mousePosition, MouseWheel::getDelta().y);
		return OneKeyInteraction::update(mousePosition);
	}
	
	SliderInteraction::SliderInteraction(SliderWheelEvent wheelEvent, PressedInteraction slideInteraction) :
		OneKeyInteraction(nullptr, slideInteraction.getKey()),
		wheelEvent(std::move(wheelEvent)),
		slideInteraction(slideInteraction) {
		event = new AddBlockInteractionEvent{this->slideInteraction};
	}
	
	SliderInteraction *SliderInteraction::copy() {
		return new SliderInteraction{wheelEvent, slideInteraction};
	}
}
