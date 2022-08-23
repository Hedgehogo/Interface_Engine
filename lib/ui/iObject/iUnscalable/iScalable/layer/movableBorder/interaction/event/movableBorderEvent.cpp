#include <iostream>
#include "movableBorderEvent.h"
#include "../../layerWithMovableBorder.hpp"

ui::MovableBorderEvent::MovableBorderEvent(ui::LayerWithMovableBorder &layer) : layer(&layer) {}

void ui::MovableBorderEvent::setLayer(ui::LayerWithMovableBorder &layer) {
    this->layer = &layer;
}

void ui::MovableBorderEvent::startPressed(sf::Vector2i mousePosition) {
    this->active = layer->isInBorder(static_cast<sf::Vector2f>(mousePosition));
    if (this->active){
        //std::cout << "Start\n";
        startMousePosition = mousePosition;
        startBorderValue = layer->getBorderValueNow();
    }
}

void ui::MovableBorderEvent::stopPressed(sf::Vector2i mousePosition) {
    this->active = false;
}

void ui::MovableBorderEvent::whilePressed(sf::Vector2i mousePosition) {
    if (this->active){
        sf::Vector2f mouseOffset = static_cast<sf::Vector2f>(mousePosition - this->startMousePosition);
        float valueOffset = 0;
        if (layer->getIsHorizontalBorder()) {
            valueOffset = mouseOffset.x / layer->getAreaSize().x;
        } else {
            valueOffset = mouseOffset.y / layer->getAreaSize().y;
        }
        layer->setBorderValue(this->startBorderValue + valueOffset);
        layer->resize(layer->getAreaSize(), layer->getAreaPosition());
        layer->setBorderValue(layer->getBorderValueNow());
    }
}

void ui::MovableBorderEvent::whileNotPressed(sf::Vector2i mousePosition) {}

void ui::MovableBorderEvent::copy(ui::MovableBorderEvent *event) {
    event->startMousePosition = this->startMousePosition;
    event->startBorderValue = this->startBorderValue;
    event->active = this->active;
}

ui::MovableBorderEvent *ui::MovableBorderEvent::copy() {
    MovableBorderEvent* event{new MovableBorderEvent{*layer}};
    MovableBorderEvent::copy(event);
    return event;
}
