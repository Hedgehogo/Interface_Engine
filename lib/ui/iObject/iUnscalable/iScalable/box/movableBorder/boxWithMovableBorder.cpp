#include "boxWithMovableBorder.hpp"
#include "../../../../../interaction/event/key/addInteraction/blockInteraction/addBlockInteractionEvent.hpp"
#include <algorithm>

namespace ui {
	BoxWithMovableBorder::BoxWithMovableBorder(
		BoxPtr<IScalable>&& firstObject,
		BoxPtr<IScalable>&& secondObject,
		bool isHorizontalBorder,
		PSCoefficient borderValue,
		int borderInteractionSize,
		sf::Vector2f minSize
	) :
		Box(minSize),
		Interactive_Simple(makeBoxPtr<IInteraction, OneKeyInteraction>(BoxPtr<KeyEvent>(new AddBlockInteractionEvent{pressedInteraction}), Key::mouseLeft)),
		firstObject(std::move(firstObject)),
		secondObject(std::move(secondObject)),
		pressedInteraction(BoxPtr<KeyEvent>{new MovableBorderEvent{*this}}, Key::mouseLeft),
		borderValueNow(borderValue->getValue()),
		borderValue(borderValue),
		borderInteractionSize(borderInteractionSize),
		isHorizontalBorder(isHorizontalBorder) {
		borderValue->addSetter([&](float value) {
			this->resize(layout.size, layout.position);
		});
	}
	
	void BoxWithMovableBorder::init(InitInfo initInfo) {
		Interactive::init(initInfo);
		firstObject->init(initInfo);
		secondObject->init(initInfo);
	}
	
	void BoxWithMovableBorder::init(InteractiveInitInfo interactiveInitInfo) {
		Interactive_Simple::init(interactiveInitInfo);
		pressedInteraction.init(InteractionInitInfo{interactiveInitInfo.toGeneral(*interactionManager, *interactionStack)});
		dynamic_cast<OneKeyInteraction&>(*this->interaction).getEvent().init({interactiveInitInfo.toGeneral(*interactionManager, *interactionStack)});
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
		if(pointPosition.x < layout.position.x || pointPosition.x > layout.position.x + layout.size.x || pointPosition.y < layout.position.y || pointPosition.y > layout.position.y + layout.size.y) {
			return false;
		}
		if(this->isHorizontalBorder) {
			int borderPosition = layout.size.x * borderValueNow + layout.position.x;
			return pointPosition.x > borderPosition - borderInteractionSize && pointPosition.x < borderPosition + borderInteractionSize;
		}
		int borderPosition = layout.size.y * borderValueNow + layout.position.y;
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
				float splitPosition = layout.position.x + layout.size.x * this->borderValueNow;
				if(splitPosition > mousePosition.x) {
					return firstObject->updateInteractions(mousePosition);
				}
				return secondObject->updateInteractions(mousePosition);
			} else {
				float splitPosition = layout.position.y + layout.size.y * this->borderValueNow;
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
	
	sf::Vector2f BoxWithMovableBorder::getMinSize() const {
		sf::Vector2f firstMinSize = firstObject->getMinSize();
		sf::Vector2f secondMinSize = secondObject->getMinSize();
		if(this->isHorizontalBorder)
			return {firstMinSize.x + secondMinSize.x, std::max(firstMinSize.y, secondMinSize.y)};
		return {std::max(firstMinSize.x, secondMinSize.x), std::max(firstMinSize.y + secondMinSize.y, this->minimumSize.y)};
	}
	
	sf::Vector2f BoxWithMovableBorder::getNormalSize() const {
		sf::Vector2f firstNormalSize = firstObject->getNormalSize();
		sf::Vector2f secondNormalSize = secondObject->getNormalSize();
		if(this->isHorizontalBorder)
			return {firstNormalSize.x + secondNormalSize.x, std::max(firstNormalSize.y, secondNormalSize.y)};
		return {std::max(firstNormalSize.x, secondNormalSize.x), firstNormalSize.y + secondNormalSize.y};
	}
	
	IScalable& BoxWithMovableBorder::getFirstObject() {
		return *firstObject;
	}
	
	const IScalable& BoxWithMovableBorder::getFirstObject() const {
		return *firstObject;
	}
	
	IScalable& BoxWithMovableBorder::getSecondObject() {
		return *secondObject;
	}
	
	const IScalable& BoxWithMovableBorder::getSecondObject() const {
		return *secondObject;
	}
	
	BoxWithMovableBorder* BoxWithMovableBorder::copy() {
		return new BoxWithMovableBorder{*this};
	}
	
	void BoxWithMovableBorder::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		firstObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		secondObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
	
	bool DecodePointer<BoxWithMovableBorder>::decodePointer(const YAML::Node& node, BoxWithMovableBorder*& boxWithMovableBorder) {
		boxWithMovableBorder = new BoxWithMovableBorder{
			node["first-object"].as<BoxPtr<IScalable> >(),
			node["first-object"].as<BoxPtr<IScalable> >(),
			convBoolDef(node["border-direction"], "horizontal", "vertical", false),
			Buffer::get<SCoefficientValue>(node["border-value"]),
			convDef(node["border-interaction-size"], 5),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}