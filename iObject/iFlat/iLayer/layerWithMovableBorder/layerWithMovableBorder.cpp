#include "layerWithMovableBorder.h"
#include "../../../../interaction/iInteraction/oneButton/oneButtonInteraction.h"
#include "../../../../interaction/iInteraction/block/pressed/pressedInteraction.h"
#include "../../../../interaction/event/button/addInteraction/addInteractionEvent.h"
#include "../../../../interaction/event/button/addInteraction/blockInteraction/addBlockInteractionEvent.h"
#include <iostream>
#include <algorithm>

ui::LayerWithMovableBorder::LayerWithMovableBorder(ui::IFlat *firstObject, ui::IFlat *secondObject, bool isHorizontalBorder,
                                                   float borderValue, int borderInteractionSize, sf::Vector2f minSize): ILayer(minSize),
                                                   pressedInteraction(new MovableBorderEvent{*this},sf::Mouse::Button::Left),
                                                   Interactive_Simple(new OneButtonInteraction{new AddInteractionEvent {pressedInteraction},sf::Mouse::Button::Left}),
                                                           firstObject(firstObject), secondObject(secondObject), isHorizontalBorder(isHorizontalBorder), borderValue(borderValue), borderValueNow(borderValue), borderInteractionSize(borderInteractionSize) {}

void ui::LayerWithMovableBorder::init(sf::RenderWindow &window, PanelManager &panelManager) {
    initObject(secondObject, window, *interactionStack, *interactionManager, panelManager);
    initObject(firstObject, window, *interactionStack, *interactionManager, panelManager);
    pressedInteraction.init(*interactionManager);
    dynamic_cast<AddInteractionEvent*>(dynamic_cast<OneButtonInteraction*>(Interactive_Simple::interaction)->getEvent())->init(*interactionManager);
}

ui::LayerWithMovableBorder::~LayerWithMovableBorder() {
    delete firstObject;
    delete secondObject;
}



void ui::LayerWithMovableBorder::draw() {
    firstObject->draw();
    secondObject->draw();
}

void ui::LayerWithMovableBorder::resize(sf::Vector2f size, sf::Vector2f position) {
    this->size = size;
    this->position = position;

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

bool ui::LayerWithMovableBorder::updateInteractions(sf::Vector2f mousePosition) {
    //return Interactive_Simple::updateInteractions(mousePosition);
    Interactive_Simple::updateInteractions(mousePosition);

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
    }
    return true;
}

sf::Vector2f ui::LayerWithMovableBorder::getMinSize() {
    sf::Vector2f firstMinSize = firstObject->getMinSize();
    sf::Vector2f secondMinSize = secondObject->getMinSize();
    if (this->isHorizontalBorder)
        return {std::max(firstMinSize.x + secondMinSize.x,this->minimumSize.x), std::max({firstMinSize.y, secondMinSize.y,this->minimumSize.y})};
    auto vvv =std::max(firstMinSize.y + secondMinSize.y,this->minimumSize.y);
    return {std::max(firstMinSize.x, secondMinSize.x), vvv};
}

sf::Vector2f ui::LayerWithMovableBorder::getNormalSize() {
    sf::Vector2f firstNormalSize = firstObject->getNormalSize();
    sf::Vector2f secondNormalSize = secondObject->getNormalSize();
    if (this->isHorizontalBorder)
        return {firstNormalSize.x + secondNormalSize.x, std::max(firstNormalSize.y, secondNormalSize.y)};
    return {std::max(firstNormalSize.x, secondNormalSize.x), firstNormalSize.y + secondNormalSize.y};
}

void ui::LayerWithMovableBorder::update() {
    Interactive_Simple::update();
    firstObject->update();
    secondObject->update();
}

ui::LayerWithMovableBorder *ui::LayerWithMovableBorder::copy() {
    LayerWithMovableBorder* layerWithMovableBorder{new LayerWithMovableBorder{firstObject->copy(), secondObject->copy(), this->isHorizontalBorder, this->borderValue,this->borderInteractionSize, this->minimumSize}};
    ILayer::copy(layerWithMovableBorder);
    return layerWithMovableBorder;
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

sf::Vector2f ui::LayerWithMovableBorder::getPosition() {
    return this->position;
}

int ui::LayerWithMovableBorder::getBorderInteractionSize() {
    return this->borderInteractionSize;
}

void ui::LayerWithMovableBorder::setBorderInteractionSize(int size) {
    this->borderInteractionSize = size;
}

sf::Vector2f ui::LayerWithMovableBorder::getSize() {
    return this->size;
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




