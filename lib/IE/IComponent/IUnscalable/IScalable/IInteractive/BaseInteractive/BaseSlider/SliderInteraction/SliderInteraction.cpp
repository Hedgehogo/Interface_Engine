#include "SliderInteraction.hpp"
#include "IE/Interaction/IEvent/KeyEvent/AddInteractionEvent/AddBlockInteractionEvent/AddBlockInteractionEvent.hpp"

namespace ui {
	SliderInteraction::SliderInteraction(BaseSlider& slider, Key key, bool wheelHorizontal, SliderWheelEvent::Relativity wheelRelativity, sf::Vector2f wheelSensitivity) :
		OneKeyInteraction(BoxPtr<KeyEvent>{new AddBlockInteractionEvent{slideInteraction}}, key),
		wheelEvent(slider, wheelHorizontal, wheelRelativity, wheelSensitivity),
		slideInteraction(BoxPtr<KeyEvent>{new SliderEvent{slider, {}}}, key) {
	}
	
	SliderInteraction::SliderInteraction(BaseSlider& slider, Key key, sf::Vector2i division, bool wheelHorizontal) :
		OneKeyInteraction(BoxPtr<KeyEvent>{new AddBlockInteractionEvent{slideInteraction}}, key),
		wheelEvent(
			slider, wheelHorizontal, SliderWheelEvent::Relativity::relationArea,
			{1.0f / static_cast<float>(division.x), 1.0f / static_cast<float>(division.y)}
		),
		slideInteraction(BoxPtr<KeyEvent>{new SliderEvent{slider, division}}, key) {
	}
	
	SliderInteraction::SliderInteraction(BaseSlider& slider, Key key, sf::Vector2i division, bool wheelHorizontal, SliderWheelEvent::Relativity wheelRelativity, sf::Vector2f wheelSensitivity) :
		OneKeyInteraction(BoxPtr<KeyEvent>{new AddBlockInteractionEvent{slideInteraction}}, key),
		wheelEvent(slider, wheelHorizontal, wheelRelativity, wheelSensitivity),
		slideInteraction(BoxPtr<KeyEvent>{new SliderEvent{slider, division}}, key) {
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
		wheelEvent(other.wheelEvent),
		slideInteraction(other.slideInteraction) {
	}
	
	SliderInteraction* SliderInteraction::copy() {
		return new SliderInteraction{*this};
	}
}
