#include "boxWithConstBorder.hpp"

namespace ui {
	void BoxWithConstBorder::init(InitInfo initInfo) {
		constObject->init(initInfo);
		secondObject->init(initInfo);
	}
	
	BoxWithConstBorder::BoxWithConstBorder(BoxPtr<IScalable>&& constObject, BoxPtr<IScalable>&& secondObject, Side side, float borderDistance, sf::Vector2f minSize) :
		Box(minSize), constObject(constObject), secondObject(secondObject), side(side), borderDistance(borderDistance) {
	}
	
	void BoxWithConstBorder::resize(sf::Vector2f size, sf::Vector2f position) {
		Box::resize(size, position);
		
		switch(side) {
			case Side::up:
				constObject->resize({size.x, borderDistance}, position);
				secondObject->resize({size.x, size.y - borderDistance}, position + sf::Vector2f(0, borderDistance));
				break;
			case Side::down:
				constObject->resize({size.x, borderDistance}, {position.x, position.y + size.y - borderDistance});
				secondObject->resize({size.x, size.y - borderDistance}, position);
				break;
			case Side::left:
				constObject->resize({borderDistance, size.y}, position);
				secondObject->resize({size.x - borderDistance, size.y}, position + sf::Vector2f(borderDistance, 0));
				break;
			case Side::right:
				constObject->resize({borderDistance, size.y}, {position.x + size.x - borderDistance, position.y});
				secondObject->resize({size.x - borderDistance, size.y}, position);
				break;
		}
	}
	
	bool BoxWithConstBorder::updateInteractions(sf::Vector2f mousePosition) {
		if(constObject->inArea(mousePosition)) {
			return constObject->updateInteractions(mousePosition);
		}
		return secondObject->updateInteractions(mousePosition);
	}
	
	sf::Vector2f BoxWithConstBorder::getMinSize() const {
		sf::Vector2f constMinSize = constObject->getMinSize();
		sf::Vector2f secondMinSize = secondObject->getMinSize();
		if(side == Side::down || side == Side::up) {
			return {std::max(constMinSize.x, secondMinSize.x), secondMinSize.y + borderDistance};
		} else {
			return {secondMinSize.x + borderDistance, std::max(constMinSize.y, secondMinSize.y)};
		}
	}
	
	sf::Vector2f BoxWithConstBorder::getNormalSize() const {
		sf::Vector2f constNormalSize = constObject->getNormalSize();
		sf::Vector2f secondNormalSize = secondObject->getNormalSize();
		if(side == Side::down || side == Side::up) {
			return {std::max(constNormalSize.x, secondNormalSize.x), secondNormalSize.y + borderDistance};
		} else {
			return {secondNormalSize.x + borderDistance, std::max(constNormalSize.y, secondNormalSize.y)};
		}
	}
	
	IScalable& BoxWithConstBorder::getFirstObject() {
		return *constObject;
	}
	
	const IScalable& BoxWithConstBorder::getFirstObject() const {
		return *constObject;
	}
	
	IScalable& BoxWithConstBorder::getSecondObject() {
		return *secondObject;
	}
	
	const IScalable& BoxWithConstBorder::getSecondObject() const {
		return *secondObject;
	}
	
	BoxWithConstBorder* BoxWithConstBorder::copy() {
		return new BoxWithConstBorder{*this};
	}
	
	void BoxWithConstBorder::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		constObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		secondObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
	
	bool DecodePointer<BoxWithConstBorder>::decodePointer(const YAML::Node& node, BoxWithConstBorder*& boxWithConstBorder) {
		boxWithConstBorder = new BoxWithConstBorder{
			node["const-object"].as<BoxPtr<IScalable> >(),
			node["second-object"].as<BoxPtr<IScalable> >(),
			node["side"].as<Side>(),
			node["border-distance"].as<float>(),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}