#include "layerWithConstBorder.h"
namespace ui {
	void LayerWithConstBorder::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		LayoutWithTwoObjects::init(renderTarget, interactionStack, interactionManager, panelManager);
	}
	
	LayerWithConstBorder::LayerWithConstBorder(IScalable *constObject, IScalable *secondObject, Side side, float borderDistance, sf::Vector2f minSize) :
		ILayer(minSize), LayoutWithTwoObjects(constObject, secondObject), side(side), borderDistance(borderDistance) {}
	
	void LayerWithConstBorder::resize(sf::Vector2f size, sf::Vector2f position) {
		ILayer::resize(size, position);
		
		switch(side) {
			case Side::up:
				firstObject->resize({size.x, borderDistance}, position);
				secondObject->resize({size.x, size.y - borderDistance}, position + sf::Vector2f(0, borderDistance));
				break;
			case Side::down:
				firstObject->resize({size.x, borderDistance}, {position.x, position.y + size.y - borderDistance});
				secondObject->resize({size.x, size.y - borderDistance}, position);
				break;
			case Side::left:
				firstObject->resize({borderDistance, size.y}, position);
				secondObject->resize({size.x - borderDistance, size.y}, position + sf::Vector2f(borderDistance, 0));
				break;
			case Side::right:
				firstObject->resize({borderDistance, size.y}, {position.x + size.x - borderDistance, position.y});
				secondObject->resize({size.x - borderDistance, size.y}, position);
				break;
		}
	}
	
	bool LayerWithConstBorder::updateInteractions(sf::Vector2f mousePosition) {
		if (firstObject->inArea(mousePosition)) {
			return firstObject->updateInteractions(mousePosition);
		}
		return secondObject->updateInteractions(mousePosition);
	}
	
	sf::Vector2f LayerWithConstBorder::getMinSize() {
		sf::Vector2f constMinSize = firstObject->getMinSize();
		sf::Vector2f secondMinSize = secondObject->getMinSize();
		if(side == Side::down || side == Side::up) {
			return {std::max(constMinSize.x, secondMinSize.x), secondMinSize.y + borderDistance};
		} else {
			return {secondMinSize.x + borderDistance, std::max(constMinSize.y, secondMinSize.y)};
		}
	}
	
	sf::Vector2f LayerWithConstBorder::getNormalSize() {
		sf::Vector2f constNormalSize = firstObject->getNormalSize();
		sf::Vector2f secondNormalSize = secondObject->getNormalSize();
		if(side == Side::down || side == Side::up) {
			return {std::max(constNormalSize.x, secondNormalSize.x), secondNormalSize.y + borderDistance};
		} else {
			return {secondNormalSize.x + borderDistance, std::max(constNormalSize.y, secondNormalSize.y)};
		}
	}
	
	LayerWithConstBorder *LayerWithConstBorder::copy() {
		LayerWithConstBorder* layerWithConstBorder{new LayerWithConstBorder{firstObject->copy(), secondObject->copy(), side, borderDistance, minimumSize}};
		ILayer::copy(layerWithConstBorder);
		return layerWithConstBorder;
	}
	
	void LayerWithConstBorder::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		firstObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
        secondObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
}