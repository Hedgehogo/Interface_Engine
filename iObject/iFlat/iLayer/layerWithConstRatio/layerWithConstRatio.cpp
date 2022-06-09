#include "layerWithConstRatio.h"

namespace ui {
	void LayerWithConstRatio::init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelStack &overlayStack) {
		initObject(constObject, window, interactionStack, interactionManager, parent, overlayStack);
		initObject(secondObject, window, interactionStack, interactionManager, parent, overlayStack);
		initObject(background, window, interactionStack, interactionManager, parent, overlayStack);
	}
	
	LayerWithConstRatio::LayerWithConstRatio(IFlat *constObject, IFlat *secondObject, IDrawn* background, float aspectRatio, Corner corner, sf::Vector2f minSize) :
		constObject(constObject), secondObject(secondObject), background(background), verticalSide(corner == Corner::UpLeft || corner == Corner::UpRight), horizontalSide(corner == Corner::UpLeft || corner == Corner::DownLeft), aspectRatio(aspectRatio),
		ILayer(minSize), constSize(), secondSize(), constPosition(), secondPosition(), renderSecond(true) {}
	
	void LayerWithConstRatio::draw(){
		background->draw();
		constObject->draw();
		if(renderSecond) {
			secondObject->draw();
		}
	}
	
	void LayerWithConstRatio::resize(sf::Vector2f size, sf::Vector2f position) {
		this->size = size;
		this->position = position;
		
		constSize = sf::Vector2f(size.x / size.y > aspectRatio ? sf::Vector2f{size.y * aspectRatio, size.y} : sf::Vector2f{size.x, size.x / aspectRatio});
		secondSize = sf::Vector2f(size.x / size.y > aspectRatio ? sf::Vector2f{size.x - constSize.x, size.y} : sf::Vector2f{size.x, size.y - constSize.y} );
		
		constPosition = sf::Vector2f{0,0};
		secondPosition = sf::Vector2f{0,0};
		
		sf::Vector2f secondMinSize = secondObject->getMinSize();
		renderSecond = secondSize.x > secondMinSize.x && secondSize.y > secondMinSize.y;
		if(renderSecond) {
			if(size.x / size.y > aspectRatio) {
				if(horizontalSide) {
					secondPosition.x = constSize.x;
				} else {
					constPosition.x = secondSize.x;
				}
			} else {
				if(verticalSide) {
					secondPosition.y = constSize.y;
				} else {
					constPosition.y = secondSize.y;
				}
			}
		} else {
			constPosition = (this->size - constSize) / 2.0f;
		}
		constObject->resize(constSize, constPosition + position);
		secondObject->resize(secondSize, secondPosition + position);
		background->resize(size, position);
	}
	
	bool LayerWithConstRatio::updateInteractions(sf::Vector2f mousePosition) {
		if(renderSecond &&
			(mousePosition.x > secondPosition.x) && (mousePosition.x < secondPosition.x + secondSize.x) &&
			(mousePosition.y > secondPosition.y) && (mousePosition.y < secondPosition.y + secondSize.y)) {
			return secondObject->updateInteractions(mousePosition);
		}
		if((mousePosition.x > constPosition.x) && (mousePosition.x < constPosition.x + constSize.x) &&
			(mousePosition.y > constPosition.y) && (mousePosition.y < constPosition.y + constSize.y)) {
			return constObject->updateInteractions(mousePosition);
		}
		return background->updateInteractions(mousePosition);
	}
	
	sf::Vector2f LayerWithConstRatio::getMinSize() {
		return constObject->getMinSize() + secondObject->getMinSize();
	}
	
	sf::Vector2f LayerWithConstRatio::getNormalSize() {
		sf::Vector2f secondNormalSize = secondObject->getNormalSize();
		sf::Vector2f constNormalSize = constObject->getNormalSize();
		return {(secondNormalSize.x > constNormalSize.x ? secondNormalSize.x : constNormalSize.x), secondNormalSize.y + constNormalSize.y};
	}
	
	void LayerWithConstRatio::update() {
		constObject->update();
		secondObject->update();
	}
}