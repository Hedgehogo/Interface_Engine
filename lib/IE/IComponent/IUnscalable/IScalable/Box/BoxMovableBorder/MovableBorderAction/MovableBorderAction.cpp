
#include "MovableBorderAction.hpp"
#include "../BoxMovableBorder.hpp"

namespace ie {
	MovableBorderAction::MovableBorderAction() : box(nullptr) {
	}
	
	void MovableBorderAction::init(BasicActionInitInfo<BoxMovableBorder&> initInfo) {
		box = &initInfo.additional;
	}
	
	void MovableBorderAction::setBox(BoxMovableBorder& box) {
		this->box = &box;
	}
	
	void MovableBorderAction::startPressed() {
		this->active = box->isInBorder(static_cast<sf::Vector2f>(mousePosition));
		if(this->active) {
			//std::cout << "Start\n";
			startMousePosition = mousePosition;
			startBorderValue = box->getBorderValueNow();
		}
	}
	
	void MovableBorderAction::stopPressed() {
		this->active = false;
	}
	
	void MovableBorderAction::whilePressed() {
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
	
	void MovableBorderAction::whileNotPressed() {
	}
	
	MovableBorderAction* MovableBorderAction::copy() {
		return new MovableBorderAction{*this};
	}
}
