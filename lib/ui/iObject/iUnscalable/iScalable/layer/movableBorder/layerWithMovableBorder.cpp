#include "layerWithMovableBorder.hpp"
#include "../../../../../interaction/event/button/addInteraction/addInteractionEvent.h"
#include "../../../../../drawable/manager/drawManager.h"
#include <algorithm>

ui::LayerWithMovableBorder::LayerWithMovableBorder(ui::IScalable *firstObject, ui::IScalable *secondObject, bool isHorizontalBorder, float borderValue, int borderInteractionSize, sf::Vector2f minSize) :
	Layer(minSize), LayoutWithTwoObjects(firstObject, secondObject),
	pressedInteraction(new MovableBorderEvent{*this},sf::Mouse::Button::Left),
	Interactive_Simple(new OneButtonInteraction{new AddInteractionEvent {pressedInteraction},sf::Mouse::Button::Left}),
	isHorizontalBorder(isHorizontalBorder), borderValue(borderValue), borderValueNow(borderValue), borderInteractionSize(borderInteractionSize) {}

void ui::LayerWithMovableBorder::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) {
	Interactive::init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
	LayoutWithTwoObjects::init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
}

void ui::LayerWithMovableBorder::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, PanelManager &panelManager) {
	Interactive_Simple::init(renderTarget, drawManager, updateManager, panelManager);
    pressedInteraction.init(*interactionManager);
    dynamic_cast<AddInteractionEvent*>(dynamic_cast<OneButtonInteraction*>(Interactive_Simple::interaction)->getEvent())->init(*interactionManager);
}

float ui::LayerWithMovableBorder::getBorderValue() {
	return this->borderValue;
}

void ui::LayerWithMovableBorder::setBorderValue(float borderValue) {
	this->borderValue = std::max(0.f,std::min(borderValue,1.f));
}

float ui::LayerWithMovableBorder::getBorderValueNow() {
	return this->borderValueNow;
}

int ui::LayerWithMovableBorder::getBorderInteractionSize() {
	return this->borderInteractionSize;
}

void ui::LayerWithMovableBorder::setBorderInteractionSize(int size) {
	this->borderInteractionSize = size;
}

bool ui::LayerWithMovableBorder::isInBorder(sf::Vector2f pointPosition) {
	if (pointPosition.x < this->position.x || pointPosition.x > this->position.x + this->size.x || pointPosition.y < this->position.y || pointPosition.y > this->position.y + this->size.y){
		return false;
	}
	if (this->isHorizontalBorder){
		int borderPosition = this->size.x * borderValueNow + this->position.x;
		return pointPosition.x > borderPosition - borderInteractionSize && pointPosition.x < borderPosition + borderInteractionSize;
	}
	int borderPosition = this->size.y * borderValueNow + this->position.y;
	return pointPosition.y > borderPosition - borderInteractionSize && pointPosition.y < borderPosition + borderInteractionSize;
}

bool ui::LayerWithMovableBorder::getIsHorizontalBorder() {
	return this->isHorizontalBorder;
}

void ui::LayerWithMovableBorder::update() {
	Interactive_Simple::update();
}

bool ui::LayerWithMovableBorder::updateInteractions(sf::Vector2f mousePosition) {
	if (!this->isInBorder(mousePosition)) {
		if (this->isHorizontalBorder){
			float splitPosition = this->position.x + this->size.x * this->borderValueNow;
			if (splitPosition > mousePosition.x){
				return firstObject->updateInteractions(mousePosition);
			}
			return secondObject->updateInteractions(mousePosition);
		}
		else{
			float splitPosition = this->position.y + this->size.y * this->borderValueNow;
			if (splitPosition > mousePosition.y){
				return firstObject->updateInteractions(mousePosition);
			}
			return secondObject->updateInteractions(mousePosition);
		}
	} else {
		Interactive_Simple::updateInteractions(mousePosition);
	}
	return true;
}

void ui::LayerWithMovableBorder::resize(sf::Vector2f size, sf::Vector2f position) {
    Layer::resize(size, position);

    sf::Vector2f firstObjectSize;
    sf::Vector2f secondObjectSize;

    sf::Vector2f firstObjectMinSize = firstObject->getMinSize();
    sf::Vector2f secondObjectMinSize = secondObject->getMinSize();

    sf::Vector2f secondPosition = position;

    if (this->isHorizontalBorder) {
        float diff  = size.x - getMinSize().x;
        float c =  secondObjectMinSize.x/firstObjectMinSize.x;
        float minSizeBorder = 1-c/(c+1);

        if (minSizeBorder > borderValue){
            borderValueNow =  std::max({firstObjectMinSize.x / size.x, borderValue});
        }
        else{
            borderValueNow =  std::min({(diff + firstObjectMinSize.x) / size.x, borderValue});
        }

        firstObjectSize = {size.x * borderValueNow, size.y};
        secondObjectSize = {size.x- firstObjectSize.x,size.y};
        secondPosition.x += firstObjectSize.x;

    }else {
        float diff  = size.y - getMinSize().y;
        float c =  secondObjectMinSize.y/firstObjectMinSize.y;
        float minSizeBorder = 1-c/(c+1);


        if (minSizeBorder > borderValue){
            borderValueNow =  std::max({firstObjectMinSize.y / size.y, borderValue});
        }
        else{
            borderValueNow =  std::min({(diff + firstObjectMinSize.y) / size.y, borderValue});
        }

        firstObjectSize = {size.x, size.y * borderValueNow};
        secondObjectSize = {size.x, size.y - firstObjectSize.y};
        secondPosition.y += firstObjectSize.y;
    }
    firstObject->resize(firstObjectSize,position);
    secondObject->resize(secondObjectSize,secondPosition);
}

sf::Vector2f ui::LayerWithMovableBorder::getMinSize() {
    sf::Vector2f firstMinSize = firstObject->getMinSize();
    sf::Vector2f secondMinSize = secondObject->getMinSize();
    if (this->isHorizontalBorder)
        return {firstMinSize.x + secondMinSize.x, std::max(firstMinSize.y, secondMinSize.y)};
    return {std::max(firstMinSize.x, secondMinSize.x), std::max(firstMinSize.y + secondMinSize.y,this->minimumSize.y)};
}

sf::Vector2f ui::LayerWithMovableBorder::getNormalSize() {
    sf::Vector2f firstNormalSize = firstObject->getNormalSize();
    sf::Vector2f secondNormalSize = secondObject->getNormalSize();
    if (this->isHorizontalBorder)
        return {firstNormalSize.x + secondNormalSize.x, std::max(firstNormalSize.y, secondNormalSize.y)};
    return {std::max(firstNormalSize.x, secondNormalSize.x), firstNormalSize.y + secondNormalSize.y};
}

ui::LayerWithMovableBorder *ui::LayerWithMovableBorder::copy() {
    LayerWithMovableBorder* layerWithMovableBorder{new LayerWithMovableBorder{firstObject->copy(), secondObject->copy(), this->isHorizontalBorder, this->borderValue,this->borderInteractionSize, this->minimumSize}};
    Layer::copy(layerWithMovableBorder);
    return layerWithMovableBorder;
}

void ui::LayerWithMovableBorder::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
    IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
    firstObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
    secondObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
}

ui::LayerWithMovableBorder *ui::LayerWithMovableBorder::createFromYaml(const YAML::Node &node) {
	ui::IScalable *firstObject;
	ui::IScalable *secondObject;
	bool isHorizontalBorder{false};
	float borderValue{0.5f};
	int borderInteractionSize{5};
	sf::Vector2f minSize{};
	node["first-object"] >> firstObject;
	node["second-object"] >> secondObject;
	std::string borderDirection;
	node["border-direction"] >> borderDirection;
	if(borderDirection == "horizontal") {
		isHorizontalBorder = true;
	} else if(borderDirection != "vertical") {
		throw YAML::BadConversion{node.Mark()};
	}
	if(node["border-value"])
		node["border-value"] >> borderValue;
	if(node["border-interaction-size"])
		node["border-interaction-size"] >> borderInteractionSize;
	if(node["min-size"])
		node["min-size"] >> minSize;
	
	return new LayerWithMovableBorder{firstObject, secondObject, isHorizontalBorder, borderValue, borderInteractionSize};
}




