#include "layerWithConstCenter.h"

namespace ui {
	void LayerWithConstCenter::init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelStack &overlayStack) {
		initObject(object, window, interactionStack, interactionManager, parent, overlayStack);
		initObject(background, window, interactionStack, interactionManager, parent, overlayStack);
	}
	
	LayerWithConstCenter::LayerWithConstCenter(IFlat* object, IDrawn* background, float aspectRatio, sf::Vector2f minSize) :
		ILayer(minSize), object(object), background(background), aspectRatio(aspectRatio), sizeOffset(0, 0) {}
	
	LayerWithConstCenter::~LayerWithConstCenter() {
		delete object;
		delete background;
	}
	
	void LayerWithConstCenter::setAspectRatio(float aspectRatio) {
		this->aspectRatio = aspectRatio;
		this->resize(size, position);
	}
	
	void LayerWithConstCenter::draw() {
		background->draw();
		object->draw();
	}
	
	void LayerWithConstCenter::resize(sf::Vector2f size, sf::Vector2f position) {
		this->size = size;
		this->position = position;
		background->resize(size, position);
		float sizeAspectRatio = size.x / size.y;
		if(sizeAspectRatio > aspectRatio) {
			size.x = size.y * aspectRatio;
		} else {
			size.y = size.x / aspectRatio;
		}
		sizeOffset = (this->size - size) / 2.0f;
		object->resize(size, position + sizeOffset);
	}
	
	bool LayerWithConstCenter::updateInteractions(sf::Vector2f mousePosition) {
		if((mousePosition.x > position.x + sizeOffset.x) && (mousePosition.x < position.x + size.x - sizeOffset.x) &&
			(mousePosition.y > position.y + sizeOffset.y) && (mousePosition.y < position.y + size.y - sizeOffset.y)) {
			return object->updateInteractions(mousePosition);
		}
		return background->updateInteractions(mousePosition);
	}
	
	sf::Vector2f LayerWithConstCenter::getMinSize() {
		sf::Vector2f maxSize {object->getMinSize()};
		sf::Vector2f backgroundSize {background->getMinSize()};
		if(maxSize.x < minimumSize.x) {
			maxSize.x = minimumSize.x;
		} else if (maxSize.x < backgroundSize.x) {
			maxSize.x = backgroundSize.x;
		}
		if(maxSize.y < minimumSize.y) {
			maxSize.y = minimumSize.y;
		} else if (maxSize.y < backgroundSize.y) {
			maxSize.y = backgroundSize.y;
		}
		return maxSize;
	}
	
	sf::Vector2f LayerWithConstCenter::getNormalSize() {
		sf::Vector2f objectNormalSize = object->getNormalSize();
		sf::Vector2f backgroundNormalSize = background->getNormalSize();
		return {(objectNormalSize.x > backgroundNormalSize.x ? objectNormalSize.x : backgroundNormalSize.x), (objectNormalSize.y > backgroundNormalSize.y ? objectNormalSize.y : backgroundNormalSize.y)};
	}
	
	void LayerWithConstCenter::update() {
		object->update();
	}
}
