#include "sliderInteraction.h"

ui::SliderInteraction::SliderInteraction(BaseSlider &slider, sf::Mouse::Button button, bool wheelHorizontal, SliderWheelEvent::Sensitivity wheelRelativity, sf::Vector2f wheelSensitivity) :
	slideInteraction(new SliderEvent{slider, {0, 0}}, button),
	OneButtonInteraction(new AddInteractionEvent{slideInteraction}, button),
	wheelEvent(slider, wheelHorizontal, wheelRelativity, wheelSensitivity) {}

ui::SliderInteraction::SliderInteraction(BaseSlider &slider, sf::Mouse::Button button, sf::Vector2i division, bool wheelHorizontal) :
	slideInteraction(new SliderEvent{slider, division}, button),
	OneButtonInteraction(new AddInteractionEvent{slideInteraction}, button),
	wheelEvent(slider, wheelHorizontal, SliderWheelEvent::Sensitivity::relationArea, {1.0f / static_cast<float>(division.x), 1.0f / static_cast<float>(division.y)}) {}

void ui::SliderInteraction::init(ui::InteractionManager &interactionManager) {
	slideInteraction.init(interactionManager);
	dynamic_cast<AddInteractionEvent*>(event)->init(interactionManager);
}

bool ui::SliderInteraction::update(sf::Vector2i mousePosition) {
	wheelEvent.update(mousePosition, sf::Wheel::value);
	return OneButtonInteraction::update(mousePosition);
}
