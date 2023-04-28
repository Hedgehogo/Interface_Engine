
#include "movableBorderEvent.hpp"
#include "../../boxWithMovableBorder.hpp"

namespace ui {
	MovableBorderEvent::MovableBorderEvent(BoxWithMovableBorder& box) : box(&box) {
	}
	
	void MovableBorderEvent::setBox(BoxWithMovableBorder& box) {
		this->box = &box;
	}
	
	void MovableBorderEvent::startPressed() {
		this->active = box->isInBorder(static_cast<sf::Vector2f>(mousePosition));
		if(this->active) {
			//std::cout << "Start\n";
			startMousePosition = mousePosition;
			startBorderValue = box->getBorderValueNow();
		}
	}
	
	void MovableBorderEvent::stopPressed() {
		this->active = false;
	}
	
	void MovableBorderEvent::whilePressed() {
		if(this->active) {
			sf::Vector2f mouseOffset = static_cast<sf::Vector2f>(mousePosition - this->startMousePosition);
			float valueOffset = 0;
			if(box->getIsHorizontalBorder()) {
				valueOffset = mouseOffset.x / box->getAreaSize().x;
			} else {
				valueOffset = mouseOffset.y / box->getAreaSize().y;
			}
			box->setBorderValue(this->startBorderValue + valueOffset);
			box->resize(box->getAreaSize(), box->getAreaPosition());
			box->setBorderValue(box->getBorderValueNow());
		}
	}
	
	void MovableBorderEvent::whileNotPressed() {
	}
	
	void MovableBorderEvent::copy(MovableBorderEvent* event) {
		event->startMousePosition = this->startMousePosition;
		event->startBorderValue = this->startBorderValue;
		event->active = this->active;
	}
	
	MovableBorderEvent* MovableBorderEvent::copy() {
		MovableBorderEvent* event{new MovableBorderEvent{*box}};
		MovableBorderEvent::copy(event);
		return event;
	}
}
