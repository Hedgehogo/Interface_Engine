#include "BoxMovableBorder.hpp"
#include "../../../../../Interaction/IEvent/KeyEvent/AddInteractionEvent/AddBlockInteractionEvent/AddBlockInteractionEvent.hpp"
#include <algorithm>

namespace ui {
	BoxMovableBorder::Make::Make(
		BoxPtr<IScalable::Make>&& firstObject,
		BoxPtr<IScalable::Make>&& secondObject,
		bool isHorizontalBorder,
		PSCoefficient borderValue,
		int borderInteractionSize,
		Key key,
		sf::Vector2f minSize
	) :
		firstObject(std::move(firstObject)),
		secondObject(std::move(secondObject)),
		isHorizontalBorder(isHorizontalBorder),
		borderValue(borderValue),
		borderInteractionSize(borderInteractionSize),
		key(key),
		minSize(minSize) {
	}
	
	BoxMovableBorder* BoxMovableBorder::Make::make(InitInfo initInfo) {
		return new BoxMovableBorder{std::move(*this), initInfo};
	}
	
	BoxMovableBorder::BoxMovableBorder(Make&& make, InitInfo initInfo) :
		Box(make.minSize),
		pressedInteraction(BoxPtr<KeyEvent>{new MovableBorderEvent{*this}}, make.key),
		interactive(makeBoxPtr<IInteraction, OneKeyInteraction>(
			BoxPtr<KeyEvent>(new AddBlockInteractionEvent{pressedInteraction}), make.key
		), initInfo),
		firstObject(make.firstObject->make(initInfo)),
		secondObject(make.secondObject->make(initInfo)),
		borderValue(make.borderValue),
		borderValueNow(borderValue->getValue()),
		borderInteractionSize(make.borderInteractionSize),
		isHorizontalBorder(make.isHorizontalBorder) {
		borderValue->addSetter([&](float) {
			this->resize(layout.size, layout.position);
		});
		initInfo.updateManager.add(*this);
		pressedInteraction.init({initInfo});
		dynamic_cast<OneKeyInteraction&>(*interactive.interaction).getEvent().init({initInfo});
	}
	
	BoxMovableBorder::BoxMovableBorder(
		BoxPtr<IScalable>&& firstObject,
		BoxPtr<IScalable>&& secondObject,
		bool isHorizontalBorder,
		PSCoefficient borderValue,
		int borderInteractionSize,
		sf::Vector2f minSize
	) :
		Box(minSize),
		pressedInteraction(BoxPtr<KeyEvent>{new MovableBorderEvent{*this}}, Key::mouseLeft),
		interactive(makeBoxPtr<IInteraction, OneKeyInteraction>(BoxPtr<KeyEvent>(new AddBlockInteractionEvent{pressedInteraction}), Key::mouseLeft)),
		firstObject(std::move(firstObject)),
		secondObject(std::move(secondObject)),
		borderValue(borderValue),
		borderValueNow(borderValue->getValue()),
		borderInteractionSize(borderInteractionSize),
		isHorizontalBorder(isHorizontalBorder) {
		borderValue->addSetter([&](float) {
			this->resize(layout.size, layout.position);
		});
	}
	
	void BoxMovableBorder::init(InitInfo initInfo) {
		interactive.init(initInfo);
		firstObject->init(initInfo);
		secondObject->init(initInfo);
		initInfo.updateManager.add(*this);
		pressedInteraction.init(InteractionInitInfo{initInfo});
		dynamic_cast<OneKeyInteraction&>(*interactive.interaction).getEvent().init({initInfo});
	}
	
	float BoxMovableBorder::getBorderValue() {
		return borderValue->getValue();
	}
	
	void BoxMovableBorder::setBorderValue(float borderValue) {
		this->borderValue->setValue(borderValue);
	}
	
	float BoxMovableBorder::getBorderValueNow() {
		return this->borderValueNow;
	}
	
	int BoxMovableBorder::getBorderInteractionSize() {
		return this->borderInteractionSize;
	}
	
	void BoxMovableBorder::setBorderInteractionSize(int size) {
		this->borderInteractionSize = size;
	}
	
	bool BoxMovableBorder::isInBorder(sf::Vector2f pointPosition) {
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
	
	bool BoxMovableBorder::getIsHorizontalBorder() {
		return this->isHorizontalBorder;
	}
	
	void BoxMovableBorder::update() {
		interactive.update();
	}
	
	bool BoxMovableBorder::updateInteractions(sf::Vector2f mousePosition) {
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
			interactive.updateInteractions();
		}
		return true;
	}
	
	void BoxMovableBorder::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		
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
	
	sf::Vector2f BoxMovableBorder::getMinSize() const {
		sf::Vector2f firstMinSize = firstObject->getMinSize();
		sf::Vector2f secondMinSize = secondObject->getMinSize();
		if(this->isHorizontalBorder)
			return {firstMinSize.x + secondMinSize.x, std::max(firstMinSize.y, secondMinSize.y)};
		return {std::max(firstMinSize.x, secondMinSize.x), std::max(firstMinSize.y + secondMinSize.y, this->minimumSize.y)};
	}
	
	sf::Vector2f BoxMovableBorder::getNormalSize() const {
		sf::Vector2f firstNormalSize = firstObject->getNormalSize();
		sf::Vector2f secondNormalSize = secondObject->getNormalSize();
		if(this->isHorizontalBorder)
			return {firstNormalSize.x + secondNormalSize.x, std::max(firstNormalSize.y, secondNormalSize.y)};
		return {std::max(firstNormalSize.x, secondNormalSize.x), firstNormalSize.y + secondNormalSize.y};
	}
	
	IScalable& BoxMovableBorder::getFirstObject() {
		return *firstObject;
	}
	
	const IScalable& BoxMovableBorder::getFirstObject() const {
		return *firstObject;
	}
	
	IScalable& BoxMovableBorder::getSecondObject() {
		return *secondObject;
	}
	
	const IScalable& BoxMovableBorder::getSecondObject() const {
		return *secondObject;
	}
	
	BoxMovableBorder* BoxMovableBorder::copy() {
		return new BoxMovableBorder{*this};
	}
	
	void BoxMovableBorder::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IComponent::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		firstObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		secondObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
	
	bool DecodePointer<BoxMovableBorder>::decodePointer(const YAML::Node& node, BoxMovableBorder*& boxWithMovableBorder) {
		boxWithMovableBorder = new BoxMovableBorder{
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