#include "sliderInteraction.hpp"
#include "../../../../../../../../interaction/event/key/addInteraction/blockInteraction/addBlockInteractionEvent.hpp"
#include <utility>

namespace ui {
	SliderInteraction::SliderInteraction(BaseSlider& slider, Key key, bool wheelHorizontal, SliderWheelEvent::Relativity wheelRelativity, sf::Vector2f wheelSensitivity) :
		OneKeyInteraction(BoxPtr<KeyEvent>{new AddBlockInteractionEvent{slideInteraction}}, key),
		slideInteraction(BoxPtr<KeyEvent>{new SliderEvent{slider, {}}}, key),
		wheelEvent(slider, wheelHorizontal, wheelRelativity, wheelSensitivity) {
	}
	
	SliderInteraction::SliderInteraction(BaseSlider& slider, Key key, sf::Vector2i division, bool wheelHorizontal) :
		OneKeyInteraction(BoxPtr<KeyEvent>{new AddBlockInteractionEvent{slideInteraction}}, key),
		slideInteraction(BoxPtr<KeyEvent>{new SliderEvent{slider, division}}, key),
		wheelEvent(
			slider, wheelHorizontal, SliderWheelEvent::Relativity::relationArea,
			{1.0f / static_cast<float>(division.x), 1.0f / static_cast<float>(division.y)}
		) {
	}
	
	void SliderInteraction::init(InteractionInitInfo interactionInitInfo) {
		slideInteraction.init(InteractionInitInfo{interactionInitInfo});
		event->init(interactionInitInfo);
	}
	
	void SliderInteraction::setSlider(BaseSlider& slider) {
		dynamic_cast<SliderEvent&>(slideInteraction.getEvent()).setSlider(slider);
		wheelEvent.setSlider(slider);
	}
	
	void SliderInteraction::update(sf::Vector2i mousePosition) {
		wheelEvent.update(mousePosition, MouseWheel::getDelta().y);
		return OneKeyInteraction::update(mousePosition);
	}
	
	SliderInteraction::SliderInteraction(const SliderInteraction& other) :
		OneKeyInteraction(BoxPtr<KeyEvent>{new AddBlockInteractionEvent{slideInteraction}}, other.key),
		slideInteraction(other.slideInteraction),
		wheelEvent(other.wheelEvent) {
	}
	
	SliderInteraction* SliderInteraction::copy() {
		return new SliderInteraction{*this};
	}
}
