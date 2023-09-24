#include "BaseSlider.hpp"
#include <cmath>

namespace ie {
	BaseSlider::BaseSlider(
		BoxPtr<IUninteractive::Make>&& slider,
		BoxPtr<IUninteractive::Make>&& background,
		BoxPtr<SliderInteraction::Make>&& interaction,
		const PSRVec2f& value,
		InitInfo initInfo
	) :
		interactive(std::move(interaction), initInfo, *this),
		background(background->make(initInfo)),
		slider(slider->make(initInfo)),
		value(value) {
		value->addSetter([&](sf::Vector2f newValue) {
			resizeSlider(newValue);
		});
		initInfo.updateManager.add(*this);
		setRangeBounds(value, {0, 0}, {1, 1});
	}
	
	BaseSlider::BaseSlider(
		BoxPtr<IUninteractive>&& slider,
		BoxPtr<IUninteractive>&& background,
		BoxPtr<SliderInteraction>&& interaction,
		const PSRVec2f& value
	) :
		interactive(std::move(interaction)),
		background(std::move(background)),
		slider(std::move(slider)),
		value(value) {
		value->addSetter([this](sf::Vector2f newValue) {
			resizeSlider(newValue);
		});
		setRangeBounds(value, {0, 0}, {1, 1});
	}
	
	BaseSlider::BaseSlider(const BaseSlider& other) :
		interactive(other.interactive),
		background(other.background),
		slider(other.slider),
		value(other.value) {
		dynamic_cast<SliderInteraction&>(*interactive.interaction).setSlider(*this);
		value->addSetter([this](sf::Vector2f newValue) {
			resizeSlider(newValue);
		});
	}
	
	void BaseSlider::init(InitInfo initInfo) {
		initInfo.updateManager.add(*this);
		interactive.init(initInfo, *this);
		background->init(initInfo);
		slider->init(initInfo);
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
	
	void BaseSlider::update() {
		interactive.update();
	}
	
	bool BaseSlider::updateInteractions(sf::Vector2f) {
		interactive.updateInteractions();
		return true;
	}
	
	void BaseSlider::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		slider->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
}
