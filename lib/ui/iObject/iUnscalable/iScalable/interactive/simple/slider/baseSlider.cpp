#include "baseSlider.hpp"
#include <cmath>

namespace ui {
	BaseSlider::BaseSlider(BoxPtr<IUninteractive>&& slider, BoxPtr<IUninteractive>&& background, const PSRVec2f& value, BoxPtr<SliderInteraction>&& interaction) :
		Interactive_Simple(dynamicCast<IInteraction>(std::move(interaction))),
		slider(std::move(slider)),
		background(std::move(background)),
		value(value) {
		value->addSetter([&](sf::Vector2f newValue) {
			resizeSlider(newValue);
		});
		setRangeBounds(value, {0, 0}, {1, 1});
	}
	
	BaseSlider::BaseSlider(const BaseSlider& other) :
		Interactive_Simple(BoxPtr{other.interaction}),
		slider(BoxPtr{other.slider}),
		background(BoxPtr{other.background}),
		value(other.value) {
		value->addSetter([&](sf::Vector2f newValue) {
			resizeSlider(newValue);
		});
		dynamic_cast<SliderInteraction&>(*interaction).setSlider(*this);
	}
	
	void BaseSlider::init(InteractiveInitInfo interactiveInitInfo) {
		Interactive_Simple::init(interactiveInitInfo);
		background->init(interactiveInitInfo.toGeneral(*interactionManager, *interactionStack));
		slider->init(interactiveInitInfo.toGeneral(*interactionManager, *interactionStack));
		dynamic_cast<SliderInteraction&>(*interaction).init(InteractionInitInfo{interactiveInitInfo.toGeneral(*interactionManager, *interactionStack)});
	}
	
	void BaseSlider::resizeSlider(sf::Vector2f newValue) {
		this->slider->resize(sliderSize, position + sf::Vector2f(moveZoneSize.x * newValue.x, moveZoneSize.y * newValue.y));
	}
	
	sf::Vector2f BaseSlider::getSliderSize() {
		return sliderSize;
	}
	
	sf::Vector2f BaseSlider::getValue() {
		return value->getValue();
	}
	
	void BaseSlider::setValue(sf::Vector2f value) {
		this->value->setValue(value);
	}
	
	PSRVec2f BaseSlider::getValuePtr() {
		return value;
	}
	
	void BaseSlider::setValueByMouse(sf::Vector2i mousePosition) {
		sf::Vector2f mouseOffset{static_cast<sf::Vector2f>(mousePosition) - position - sliderSize / 2.0f};
		value->setValue({(moveZoneSize.x != 0 ? mouseOffset.x / moveZoneSize.x : 0), (moveZoneSize.y != 0 ? mouseOffset.y / moveZoneSize.y : 0)});
	}
	
	sf::Vector2f BaseSlider::roundValueToDivision(sf::Vector2f value, sf::Vector2i division) {
		sf::Vector2f divisions{division};
		if(division.x != 0) {
			value.x = std::round(value.x * divisions.x) / divisions.x;
		}
		if(division.y != 0) {
			value.y = std::round(value.y * divisions.y) / divisions.y;
		}
		return value;
	}
	
	sf::Vector2f BaseSlider::moveSlider(sf::Vector2f value, sf::Vector2f offset) const {
		if(moveZoneSize.x != 0) {
			value.x += offset.x / moveZoneSize.x;
		}
		if(moveZoneSize.y != 0) {
			value.y += offset.y / moveZoneSize.y;
		}
		return value;
	}
	
	bool BaseSlider::onSlider(sf::Vector2i mousePosition) {
		sf::Vector2f mouse{static_cast<sf::Vector2f>(mousePosition)};
		sf::Vector2f sliderPosition{position.x + value->getX() * moveZoneSize.x, position.y + value->getY() * moveZoneSize.y};
		return
			mouse.x > sliderPosition.x && mouse.x < sliderPosition.x + sliderSize.x &&
			mouse.y > sliderPosition.y && mouse.y < sliderPosition.y + sliderSize.y;
	}
	
	sf::Vector2f BaseSlider::getAreaPosition() const {
		return position;
	}
	
	sf::Vector2f BaseSlider::getAreaSize() const {
		return sliderSize + moveZoneSize;
	}
	
	sf::Vector2f BaseSlider::getMinSize() const {
		return background->getMinSize();
	}
	
	sf::Vector2f BaseSlider::getNormalSize() const {
		return background->getNormalSize();
	}
	
	void BaseSlider::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		slider->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
}
