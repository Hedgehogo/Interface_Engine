#include "SliderInteraction.hpp"
#include "IE/Interaction/IAction/BasicKeyAction/BasicAddInteractionAction/BasicAddBlockInteractionAction/BasicAddBlockInteractionAction.hpp"

namespace ie {
	SliderInteraction::SliderInteraction(BaseSlider& slider, Key key, bool wheelHorizontal, SliderWheelAction::Relativity wheelRelativity, sf::Vector2f wheelSensitivity) :
		OneKeyInteraction(BoxPtr<KeyAction>{new AddBlockInteractionAction{slideInteraction}}, key),
		wheelAction(slider, wheelHorizontal, wheelRelativity, wheelSensitivity),
		slideInteraction(BoxPtr<KeyAction>{new SliderAction{slider, {}}}, key) {
	}
	
	SliderInteraction::SliderInteraction(BaseSlider& slider, Key key, sf::Vector2i division, bool wheelHorizontal) :
		OneKeyInteraction(BoxPtr<KeyAction>{new AddBlockInteractionAction{slideInteraction}}, key),
		wheelAction(
			slider, wheelHorizontal, SliderWheelAction::Relativity::relationArea,
			{1.0f / static_cast<float>(division.x), 1.0f / static_cast<float>(division.y)}
		),
		slideInteraction(BoxPtr<KeyAction>{new SliderAction{slider, division}}, key) {
	}
	
	SliderInteraction::SliderInteraction(BaseSlider& slider, Key key, sf::Vector2i division, bool wheelHorizontal, SliderWheelAction::Relativity wheelRelativity, sf::Vector2f wheelSensitivity) :
		OneKeyInteraction(BoxPtr<KeyAction>{new AddBlockInteractionAction{slideInteraction}}, key),
		wheelAction(slider, wheelHorizontal, wheelRelativity, wheelSensitivity),
		slideInteraction(BoxPtr<KeyAction>{new SliderAction{slider, division}}, key) {
	}
	
	void SliderInteraction::init(ActionInitInfo initInfo) {
		slideInteraction.init(initInfo);
		action->init(initInfo);
	}
	
	void SliderInteraction::setSlider(BaseSlider& slider) {
		dynamic_cast<SliderAction&>(slideInteraction.getAction()).setSlider(slider);
		wheelAction.setSlider(slider);
	}
	
	void SliderInteraction::update(sf::Vector2i mousePosition) {
		wheelAction.update(mousePosition, MouseWheel::getDelta().y);
		return OneKeyInteraction::update(mousePosition);
	}
	
	SliderInteraction::SliderInteraction(const SliderInteraction& other) :
		OneKeyInteraction(BoxPtr<KeyAction>{new AddBlockInteractionAction{slideInteraction}}, other.key),
		wheelAction(other.wheelAction),
		slideInteraction(other.slideInteraction) {
	}
	
	SliderInteraction* SliderInteraction::copy() {
		return new SliderInteraction{*this};
	}
}
