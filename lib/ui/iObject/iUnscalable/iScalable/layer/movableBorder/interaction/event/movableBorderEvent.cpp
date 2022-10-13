
#include "movableBorderEvent.hpp"
#include "../../layerWithMovableBorder.hpp"

namespace ui {
	MovableBorderEvent::MovableBorderEvent(LayerWithMovableBorder &layer) : layer(&layer) {}
	
	void MovableBorderEvent::setLayer(LayerWithMovableBorder &layer) {
		this->layer = &layer;
	}
	
	void MovableBorderEvent::startPressed() {
		this->active = layer->isInBorder(static_cast<sf::Vector2f>(mousePosition));
		if(this->active) {
			//std::cout << "Start\n";
			startMousePosition = mousePosition;
			startBorderValue = layer->getBorderValueNow();
		}
	}
	
	void MovableBorderEvent::stopPressed() {
		this->active = false;
	}
	
	void MovableBorderEvent::whilePressed() {
		if(this->active) {
			sf::Vector2f mouseOffset = static_cast<sf::Vector2f>(mousePosition - this->startMousePosition);
			float valueOffset = 0;
			if(layer->getIsHorizontalBorder()) {
				valueOffset = mouseOffset.x / layer->getAreaSize().x;
			} else {
				valueOffset = mouseOffset.y / layer->getAreaSize().y;
			}
			layer->setBorderValue(this->startBorderValue + valueOffset);
			layer->resize(layer->getAreaSize(), layer->getAreaPosition());
			layer->setBorderValue(layer->getBorderValueNow());
		}
	}
	
	void MovableBorderEvent::whileNotPressed() {}
	
	void MovableBorderEvent::copy(MovableBorderEvent *event) {
		event->startMousePosition = this->startMousePosition;
		event->startBorderValue = this->startBorderValue;
		event->active = this->active;
	}
	
	MovableBorderEvent *MovableBorderEvent::copy() {
		MovableBorderEvent *event{new MovableBorderEvent{*layer}};
		MovableBorderEvent::copy(event);
		return event;
	}
}
