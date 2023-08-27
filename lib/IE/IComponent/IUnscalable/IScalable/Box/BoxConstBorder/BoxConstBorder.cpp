#include "BoxConstBorder.hpp"

namespace ie {
	BoxConstBorder::Make::Make(
		BoxPtr<IScalable::Make>&& constObject,
		BoxPtr<IScalable::Make>&& secondObject,
		float borderDistance,
		Side side,
		sf::Vector2f minSize
	) : constObject(std::move(constObject)), secondObject(std::move(secondObject)), borderDistance(borderDistance), side(side), minSize(minSize) {
	}
	
	BoxConstBorder* BoxConstBorder::Make::make(InitInfo initInfo) {
		return new BoxConstBorder{std::move(*this), initInfo};
	}
	
	BoxConstBorder::BoxConstBorder(Make&& make, InitInfo initInfo) :
		Box(make.minSize),
		constObject(make.constObject->make(initInfo)),
		secondObject(make.secondObject->make(initInfo)),
		borderDistance(make.borderDistance),
		side(make.side) {
	}
	
	BoxConstBorder::BoxConstBorder(BoxPtr<IScalable>&& constObject, BoxPtr<IScalable>&& secondObject, Side side, float borderDistance, sf::Vector2f minSize) :
		Box(minSize), constObject(std::move(constObject)), secondObject(std::move(secondObject)), borderDistance(borderDistance), side(side) {
	}
	
	void BoxConstBorder::init(InitInfo initInfo) {
		constObject->init(initInfo);
		secondObject->init(initInfo);
	}
	
	void BoxConstBorder::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		
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
	
	bool BoxConstBorder::updateInteractions(sf::Vector2f mousePosition) {
		if(constObject->inArea(mousePosition)) {
			return constObject->updateInteractions(mousePosition);
		}
		return secondObject->updateInteractions(mousePosition);
	}
	
	sf::Vector2f BoxConstBorder::getMinSize() const {
		sf::Vector2f constMinSize = constObject->getMinSize();
		sf::Vector2f secondMinSize = secondObject->getMinSize();
		if(side == Side::down || side == Side::up) {
			return {std::max(constMinSize.x, secondMinSize.x), secondMinSize.y + borderDistance};
		} else {
			return {secondMinSize.x + borderDistance, std::max(constMinSize.y, secondMinSize.y)};
		}
	}
	
	sf::Vector2f BoxConstBorder::getNormalSize() const {
		sf::Vector2f constNormalSize = constObject->getNormalSize();
		sf::Vector2f secondNormalSize = secondObject->getNormalSize();
		if(side == Side::down || side == Side::up) {
			return {std::max(constNormalSize.x, secondNormalSize.x), secondNormalSize.y + borderDistance};
		} else {
			return {secondNormalSize.x + borderDistance, std::max(constNormalSize.y, secondNormalSize.y)};
		}
	}
	
	IScalable& BoxConstBorder::getFirstObject() {
		return *constObject;
	}
	
	const IScalable& BoxConstBorder::getFirstObject() const {
		return *constObject;
	}
	
	IScalable& BoxConstBorder::getSecondObject() {
		return *secondObject;
	}
	
	const IScalable& BoxConstBorder::getSecondObject() const {
		return *secondObject;
	}
	
	BoxConstBorder* BoxConstBorder::copy() {
		return new BoxConstBorder{*this};
	}
	
	void BoxConstBorder::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IComponent::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		constObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		secondObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
	
	bool DecodePointer<BoxConstBorder>::decodePointer(const YAML::Node& node, BoxConstBorder*& boxWithConstBorder) {
		boxWithConstBorder = new BoxConstBorder{
			node["const-object"].as<BoxPtr<IScalable> >(),
			node["second-object"].as<BoxPtr<IScalable> >(),
			node["side"].as<Side>(),
			node["border-distance"].as<float>(),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}