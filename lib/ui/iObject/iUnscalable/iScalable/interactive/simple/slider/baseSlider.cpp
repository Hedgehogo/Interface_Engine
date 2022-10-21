#include "baseSlider.hpp"
#include <cmath>

namespace ui {
	void BaseSlider::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, IPanelManager &panelManager) {
		Interactive_Simple::init(renderTarget, drawManager, updateManager, panelManager);
		drawManager.add(*this);
		background->init(renderTarget, drawManager, updateManager, *interactionManager, *interactionStack, panelManager);
		slider->init(renderTarget, drawManager, updateManager, *interactionManager, *interactionStack, panelManager);
		dynamic_cast<SliderInteraction *>(interaction)->init(*interactionManager);
	}
	
	BaseSlider::BaseSlider(IUninteractive *slider, IUninteractive *background, const PSCoefficientVec2 &value, SliderInteraction *interaction) :
		Interactive_Simple(interaction), slider(slider), background(background), value(value), position(), sliderSize(), moveZoneSize() {}
	
	void BaseSlider::cutBackValue() {
		//value.x = std::max(0.f,std::min(1.f,value.x));
		//value.y = std::max(0.f,std::min(1.f,value.y));
	}
	
	sf::Vector2f BaseSlider::getSliderSize() {
		return sliderSize;
	}
	
	sf::Vector2f BaseSlider::getValue() {
		return value->getValue();
	}
	
	void BaseSlider::setValue(sf::Vector2f value) {
		this->value->setValue(value);
		//cutBackValue();
	}
	
	void BaseSlider::setValueByMouse(sf::Vector2i mousePosition) {
		sf::Vector2f mouseOffset{static_cast<sf::Vector2f>(mousePosition) - position - sliderSize / 2.0f};
		value->setValue({(moveZoneSize.x != 0 ? mouseOffset.x / moveZoneSize.x : 0), (moveZoneSize.y != 0 ? mouseOffset.y / moveZoneSize.y : 0)});
		//cutBackValue();
	}
	
	void BaseSlider::roundValueToDivision(sf::Vector2i division) {
		sf::Vector2f divisions{static_cast<sf::Vector2f>(division)};
		if(division.x != 0)
			value->setX(std::round(value->getX() * divisions.x) / divisions.x);
		if(division.y != 0)
			value->setY(std::round(value->getY() * divisions.y) / divisions.y);
	}
	
	bool BaseSlider::onSlider(sf::Vector2i mousePosition) {
		sf::Vector2f mouse{static_cast<sf::Vector2f>(mousePosition)};
		sf::Vector2f sliderPosition{position.x + value->getX() * moveZoneSize.x, position.y + value->getY() * moveZoneSize.y};
		return mouse.x > sliderPosition.x && mouse.x < sliderPosition.x + sliderSize.x &&
			   mouse.y > sliderPosition.y && mouse.y < sliderPosition.y + sliderSize.y;
	}
	
	void BaseSlider::moveSlider(sf::Vector2i mouseOffset) {
		if(moveZoneSize.x != 0)
			value->setX(value->getX() + static_cast<float>(mouseOffset.x) / moveZoneSize.x);
		if(moveZoneSize.y != 0)
			value->setY(value->getY() + static_cast<float>(mouseOffset.y) / moveZoneSize.y);
		//cutBackValue();
	}
	
	void BaseSlider::draw() {
		slider->resize(sliderSize, position + sf::Vector2f(moveZoneSize.x * value->getX(), moveZoneSize.y * value->getY()));
	}
	
	sf::Vector2f BaseSlider::getAreaPosition() {
		return position;
	}
	
	sf::Vector2f BaseSlider::getAreaSize() {
		return sliderSize + moveZoneSize;
	}
	
	sf::Vector2f BaseSlider::getMinSize() {
		return background->getMinSize();
	}
	
	sf::Vector2f BaseSlider::getNormalSize() {
		return background->getNormalSize();
	}
	
	void BaseSlider::copy(BaseSlider *baseSlider) {
		Interactive_Simple::copy(baseSlider);
		baseSlider->value = this->value;
		baseSlider->position = this->position;
		baseSlider->sliderSize = this->sliderSize;
		baseSlider->moveZoneSize = this->moveZoneSize;
	}
	
	void BaseSlider::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		slider->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
}
