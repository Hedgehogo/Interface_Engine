#include "baseSlider.h"
#include <cmath>

void ui::BaseSlider::init(sf::RenderTarget &renderTarget, PanelManager &panelManager) {
	initObject(background, renderTarget, *interactionStack, *interactionManager, panelManager);
	initObject(slider, renderTarget, *interactionStack, *interactionManager, panelManager);
	dynamic_cast<SliderInteraction*>(interaction)->init(*interactionManager);
}

ui::BaseSlider::BaseSlider(ui::IDrawable *slider, ui::IDrawable *background, SliderInteraction* interaction) :
	Interactive_Simple(interaction), slider(slider), background(background), value(), position(), sliderSize(), moveZoneSize() {}

void ui::BaseSlider::cutBackValue() {
    value.x = std::max(0.f,std::min(1.f,value.x));
    value.y = std::max(0.f,std::min(1.f,value.y));
}

sf::Vector2f ui::BaseSlider::getSliderSize() {
	return sliderSize;
}

const sf::Vector2f &ui::BaseSlider::getValue() {
	return value;
}

void ui::BaseSlider::setValue(sf::Vector2f newValue) {
	value = newValue;
	cutBackValue();
}

void ui::BaseSlider::setValueByMouse(sf::Vector2i mousePosition) {
	sf::Vector2f mouseOffset {static_cast<sf::Vector2f>(mousePosition) - position - sliderSize / 2.0f};
	value = {(moveZoneSize.x != 0 ? mouseOffset.x / moveZoneSize.x : 0), (moveZoneSize.y != 0 ? mouseOffset.y / moveZoneSize.y : 0)};
	cutBackValue();
}

void ui::BaseSlider::roundValueToDivision(sf::Vector2i division) {
	sf::Vector2f divisions{static_cast<sf::Vector2f>(division)};
	if(division.x != 0)
		value.x = std::round(value.x * divisions.x) / divisions.x;
	if(division.y != 0)
		value.y = std::round(value.y * divisions.y) / divisions.y;
}

bool ui::BaseSlider::onSlider(sf::Vector2i mousePosition) {
	sf::Vector2f mouse {static_cast<sf::Vector2f>(mousePosition)};
	sf::Vector2f sliderPosition {position.x + value.x * moveZoneSize.x, position.y + value.y * moveZoneSize.y};
	return mouse.x > sliderPosition.x && mouse.x < sliderPosition.x + sliderSize.x &&
		   mouse.y > sliderPosition.y && mouse.y < sliderPosition.y + sliderSize.y;
}

void ui::BaseSlider::move(sf::Vector2i mouseOffset) {
	if(moveZoneSize.x != 0)
		value.x += static_cast<float>(mouseOffset.x) / moveZoneSize.x;
	if(moveZoneSize.y != 0)
		value.y += static_cast<float>(mouseOffset.y) / moveZoneSize.y;
	cutBackValue();
}

void ui::BaseSlider::draw() {
	background->draw();
	slider->resize(sliderSize, position + sf::Vector2f(moveZoneSize.x * value.x, moveZoneSize.y * value.y));
	slider->draw();
}

sf::Vector2f ui::BaseSlider::getAreaPosition() {
	return position;
}

sf::Vector2f ui::BaseSlider::getAreaSize() {
	return sliderSize + moveZoneSize;
}

sf::Vector2f ui::BaseSlider::getMinSize() {
	return background->getMinSize();
}

sf::Vector2f ui::BaseSlider::getNormalSize() {
	return background->getNormalSize();
}

void ui::BaseSlider::copy(ui::BaseSlider *baseSlider) {
	Interactive_Simple::copy(baseSlider);
	baseSlider->value = this->value;
	baseSlider->position = this->position;
	baseSlider->sliderSize = this->sliderSize;
	baseSlider->moveZoneSize = this->moveZoneSize;
}

void ui::BaseSlider::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
    background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
    slider->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
}
