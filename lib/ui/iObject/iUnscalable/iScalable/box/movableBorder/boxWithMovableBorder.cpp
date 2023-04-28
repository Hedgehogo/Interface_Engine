#include "boxWithMovableBorder.hpp"
#include "../../../../../interaction/event/key/addInteraction/blockInteraction/addBlockInteractionEvent.hpp"
#include <algorithm>

namespace ui {
	BoxWithMovableBorder::BoxWithMovableBorder(IScalable *firstObject, IScalable *secondObject, bool isHorizontalBorder, PSCoefficient borderValue, int borderInteractionSize, sf::Vector2f minSize) :
		Box(minSize), LayoutWithTwoObjects(firstObject, secondObject),
		pressedInteraction(new MovableBorderEvent{*this}, Key::mouseLeft),
		Interactive_Simple(new OneKeyInteraction{new AddBlockInteractionEvent{pressedInteraction}, Key::mouseLeft}),
		isHorizontalBorder(isHorizontalBorder), borderValue(borderValue), borderValueNow(borderValue->getValue()), borderInteractionSize(borderInteractionSize) {
		
		borderValue->addSetter([&](float value) {
			this->resize(this->size, this->position);
		});
	}
	
	void
	BoxWithMovableBorder::init(InitInfo initInfo) {
		Interactive::init(initInfo);
		LayoutWithTwoObjects::init(initInfo);
	}
	
	void BoxWithMovableBorder::init(InteractiveInitInfo interactiveInitInfo) {
		Interactive_Simple::init(interactiveInitInfo);
		pressedInteraction.init(*interactionManager);
		dynamic_cast<AddBlockInteractionEvent *>(dynamic_cast<OneKeyInteraction *>(Interactive_Simple::interaction)->getEvent())->init(*interactionManager);
	}
	
	float BoxWithMovableBorder::getBorderValue() {
		return borderValue->getValue();
	}
	
	void BoxWithMovableBorder::setBorderValue(float borderValue) {
		this->borderValue->setValue(borderValue);
	}
	
	float BoxWithMovableBorder::getBorderValueNow() {
		return this->borderValueNow;
	}
	
	int BoxWithMovableBorder::getBorderInteractionSize() {
		return this->borderInteractionSize;
	}
	
	void BoxWithMovableBorder::setBorderInteractionSize(int size) {
		this->borderInteractionSize = size;
	}
	
	bool BoxWithMovableBorder::isInBorder(sf::Vector2f pointPosition) {
		if(pointPosition.x < this->position.x || pointPosition.x > this->position.x + this->size.x || pointPosition.y < this->position.y || pointPosition.y > this->position.y + this->size.y) {
			return false;
		}
		if(this->isHorizontalBorder) {
			int borderPosition = this->size.x * borderValueNow + this->position.x;
			return pointPosition.x > borderPosition - borderInteractionSize && pointPosition.x < borderPosition + borderInteractionSize;
		}
		int borderPosition = this->size.y * borderValueNow + this->position.y;
		return pointPosition.y > borderPosition - borderInteractionSize && pointPosition.y < borderPosition + borderInteractionSize;
	}
	
	bool BoxWithMovableBorder::getIsHorizontalBorder() {
		return this->isHorizontalBorder;
	}
	
	void BoxWithMovableBorder::update() {
		Interactive_Simple::update();
	}
	
	bool BoxWithMovableBorder::updateInteractions(sf::Vector2f mousePosition) {
		if(!this->isInBorder(mousePosition)) {
			if(this->isHorizontalBorder) {
				float splitPosition = this->position.x + this->size.x * this->borderValueNow;
				if(splitPosition > mousePosition.x) {
					return firstObject->updateInteractions(mousePosition);
				}
				return secondObject->updateInteractions(mousePosition);
			} else {
				float splitPosition = this->position.y + this->size.y * this->borderValueNow;
				if(splitPosition > mousePosition.y) {
					return firstObject->updateInteractions(mousePosition);
				}
				return secondObject->updateInteractions(mousePosition);
			}
		} else {
			Interactive_Simple::updateInteractions(mousePosition);
		}
		return true;
	}
	
	void BoxWithMovableBorder::resize(sf::Vector2f size, sf::Vector2f position) {
		Box::resize(size, position);

		sf::Vector2f firstObjectSize;
		sf::Vector2f secondObjectSize;
		
		sf::Vector2f firstObjectMinSize = firstObject->getMinSize();
		sf::Vector2f secondObjectMinSize = secondObject->getMinSize();
		
		sf::Vector2f secondPosition = position;
		
		if(this->isHorizontalBorder) {
			float c = secondObjectMinSize.x / firstObjectMinSize.x;
			float minSizeBorder = 1 - c / (c + 1);
			
			if(minSizeBorder > borderValue->getValue()) {
				borderValueNow = std::max({firstObjectMinSize.x / size.x, borderValue->getValue()});
			} else {
				float diff = size.x - getMinSize().x;
				borderValueNow = std::min({(diff + firstObjectMinSize.x) / size.x, borderValue->getValue()});
			}
			
			firstObjectSize = {size.x * borderValueNow, size.y};
			secondObjectSize = {size.x - firstObjectSize.x, size.y};
			secondPosition.x += firstObjectSize.x;
			
		} else {
			float c = secondObjectMinSize.y / firstObjectMinSize.y;
			float minSizeBorder = 1 - c / (c + 1);
			
			if(minSizeBorder > borderValue->getValue()) {
				borderValueNow = std::max({firstObjectMinSize.y / size.y, borderValue->getValue()});
			} else {
				float diff = size.y - getMinSize().y;
				borderValueNow = std::min({(diff + firstObjectMinSize.y) / size.y, borderValue->getValue()});
			}
			
			firstObjectSize = {size.x, size.y * borderValueNow};
			secondObjectSize = {size.x, size.y - firstObjectSize.y};
			secondPosition.y += firstObjectSize.y;
		}
		firstObject->resize(firstObjectSize, position);
		secondObject->resize(secondObjectSize, secondPosition);
	}
	
	sf::Vector2f BoxWithMovableBorder::getMinSize() {
		sf::Vector2f firstMinSize = firstObject->getMinSize();
		sf::Vector2f secondMinSize = secondObject->getMinSize();
		if(this->isHorizontalBorder)
			return {firstMinSize.x + secondMinSize.x, std::max(firstMinSize.y, secondMinSize.y)};
		return {std::max(firstMinSize.x, secondMinSize.x), std::max(firstMinSize.y + secondMinSize.y, this->minimumSize.y)};
	}
	
	sf::Vector2f BoxWithMovableBorder::getNormalSize() {
		sf::Vector2f firstNormalSize = firstObject->getNormalSize();
		sf::Vector2f secondNormalSize = secondObject->getNormalSize();
		if(this->isHorizontalBorder)
			return {firstNormalSize.x + secondNormalSize.x, std::max(firstNormalSize.y, secondNormalSize.y)};
		return {std::max(firstNormalSize.x, secondNormalSize.x), firstNormalSize.y + secondNormalSize.y};
	}
	
	BoxWithMovableBorder *BoxWithMovableBorder::copy() {
		BoxWithMovableBorder *boxWithMovableBorder{new BoxWithMovableBorder{firstObject->copy(), secondObject->copy(), this->isHorizontalBorder, this->borderValue, this->borderInteractionSize, this->minimumSize}};
		Box::copy(boxWithMovableBorder);
		return boxWithMovableBorder;
	}
	
	void BoxWithMovableBorder::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		firstObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		secondObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
	
	bool convertPointer(const YAML::Node &node, BoxWithMovableBorder *&boxWithMovableBorder) {
		IScalable *firstObject;
		IScalable *secondObject;
		bool isHorizontalBorder{false};
		PSCoefficient borderValue;
		int borderInteractionSize{5};
		sf::Vector2f minSize{};
		node["first-object"] >> firstObject;
		node["second-object"] >> secondObject;
		std::string borderDirection;
		node["border-direction"] >> borderDirection;
		borderValue = Buffer::get<SCoefficientValue>(node["border-value"]);
		if(borderDirection == "horizontal") {
			isHorizontalBorder = true;
		} else if(borderDirection != "vertical") {
			throw YAML::BadConversion{node.Mark()};
		}
		if(node["border-interaction-size"])
			node["border-interaction-size"] >> borderInteractionSize;
		if(node["min-size"])
			node["min-size"] >> minSize;
		
		boxWithMovableBorder = new BoxWithMovableBorder{firstObject, secondObject, isHorizontalBorder, borderValue, borderInteractionSize};
		return true;
	}
	
	bool DecodePointer<BoxWithMovableBorder>::decodePointer(const YAML::Node &node, BoxWithMovableBorder *&boxWithMovableBorder) {
		IScalable *firstObject;
		IScalable *secondObject;
		bool isHorizontalBorder{false};
		PSCoefficient borderValue;
		int borderInteractionSize{5};
		sf::Vector2f minSize{};
		node["first-object"] >> firstObject;
		node["second-object"] >> secondObject;
		std::string borderDirection;
		node["border-direction"] >> borderDirection;
		borderValue = Buffer::get<SCoefficientValue>(node["border-value"]);
		if(borderDirection == "horizontal") {
			isHorizontalBorder = true;
		} else if(borderDirection != "vertical") {
			throw YAML::BadConversion{node.Mark()};
		}
		if(node["border-interaction-size"])
			node["border-interaction-size"] >> borderInteractionSize;
		if(node["min-size"])
			node["min-size"] >> minSize;
		
		boxWithMovableBorder = new BoxWithMovableBorder{firstObject, secondObject, isHorizontalBorder, borderValue, borderInteractionSize};
		return true;
	}
}