#include "layerWithConstBorder.h"
namespace ui {
	void LayerWithConstBorder::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		initObject(secondObject, renderTarget, interactionStack, interactionManager, panelManager);
		initObject(constObject, renderTarget, interactionStack, interactionManager, panelManager);
	}
	
	LayerWithConstBorder::LayerWithConstBorder(IFlat *constObject, IFlat *secondObject, Side side, float borderDistance, sf::Vector2f minSize) :
		ILayer(minSize), constObject(constObject), side(side), secondObject(secondObject), borderDistance(borderDistance) {}

    LayerWithConstBorder::~LayerWithConstBorder() {
        delete constObject;
        delete secondObject;
    }

	void LayerWithConstBorder::draw() {
		constObject->draw();
		secondObject->draw();
	}
	
	void LayerWithConstBorder::resize(sf::Vector2f size, sf::Vector2f position) {
		ILayer::resize(size, position);
		
		switch(side) {
			case Side::Up :
				positionConstObject = position;
				sizeConstObject = {size.x, borderDistance};
				constObject->resize(sizeConstObject, positionConstObject);
				secondObject->resize({size.x, size.y - borderDistance}, position + sf::Vector2f(0, borderDistance));
				break;
			case Side::Down:
				positionConstObject = position + sf::Vector2f(0, size.y - borderDistance);
				sizeConstObject = {size.x, borderDistance};
				constObject->resize(sizeConstObject, positionConstObject);
				secondObject->resize({size.x, size.y - borderDistance}, position);
				break;
			case Side::Left:
				positionConstObject = position;
				sizeConstObject = {borderDistance, size.y};
				constObject->resize(sizeConstObject, positionConstObject);
				secondObject->resize({size.x - borderDistance, size.y}, position + sf::Vector2f(borderDistance, 0));
				break;
			case Side::Right:
				positionConstObject = position + sf::Vector2f(size.x - borderDistance, 0);
				sizeConstObject = {borderDistance, size.y};
				constObject->resize(sizeConstObject, positionConstObject);
				secondObject->resize({size.x - borderDistance, size.y}, position);
				break;
		}
		
	}
	
	bool LayerWithConstBorder::updateInteractions(sf::Vector2f mousePosition) {
		if (mousePosition.x > positionConstObject.x && mousePosition.x < positionConstObject.x + sizeConstObject.x &&
			mousePosition.y > positionConstObject.y && mousePosition.y < positionConstObject.y + sizeConstObject.y) {
			return constObject->updateInteractions(mousePosition);
		}
		return secondObject->updateInteractions(mousePosition);
	}
	
	sf::Vector2f LayerWithConstBorder::getMinSize() {
		sf::Vector2f constMinSize = constObject->getMinSize();
		sf::Vector2f secondMinSize = secondObject->getMinSize();
		if(side == Side::Down || side == Side::Up) {
			return {std::max(constMinSize.x, secondMinSize.x), secondMinSize.y + borderDistance};
		} else {
			return {secondMinSize.x + borderDistance, std::max(constMinSize.y, secondMinSize.y)};
		}
	}
	
	sf::Vector2f LayerWithConstBorder::getNormalSize() {
		sf::Vector2f constNormalSize = constObject->getNormalSize();
		sf::Vector2f secondNormalSize = secondObject->getNormalSize();
		if(side == Side::Down || side == Side::Up) {
			return {std::max(constNormalSize.x, secondNormalSize.x), secondNormalSize.y + borderDistance};
		} else {
			return {secondNormalSize.x + borderDistance, std::max(constNormalSize.y, secondNormalSize.y)};
		}
	}
	
	void LayerWithConstBorder::update() {
		constObject->update();
		secondObject->update();
	}
	
	void LayerWithConstBorder::copy(LayerWithConstBorder *layerWithConstBorder) {
		ILayer::copy(layerWithConstBorder);
		layerWithConstBorder->positionConstObject = this->positionConstObject;
		layerWithConstBorder->sizeConstObject = this->sizeConstObject;
	}
	
	LayerWithConstBorder *LayerWithConstBorder::copy() {
		LayerWithConstBorder* layerWithConstBorder{new LayerWithConstBorder{constObject->copy(), secondObject->copy(), side, borderDistance, minimumSize}};
		LayerWithConstBorder::copy(layerWithConstBorder);
		return layerWithConstBorder;
	}
	
	void LayerWithConstBorder::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
        constObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
        secondObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
}