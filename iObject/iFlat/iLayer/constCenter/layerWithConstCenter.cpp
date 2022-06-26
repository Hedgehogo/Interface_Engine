#include "layerWithConstCenter.h"

namespace ui {
	void LayerWithConstCenter::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		initObject(object, renderTarget, interactionStack, interactionManager, panelManager);
		initObject(background, renderTarget, interactionStack, interactionManager, panelManager);
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
		ILayer::resize(size, position);
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
		sf::Vector2f objectMinSize {object->getMinSize()};
		sf::Vector2f backgroundMinSize {background->getMinSize()};
		objectMinSize = sf::Vector2f{std::max(objectMinSize.x, objectMinSize.y * aspectRatio), std::max(objectMinSize.y, objectMinSize.x / aspectRatio)};
		return {std::max({objectMinSize.x, backgroundMinSize.x, minimumSize.x}), std::max({objectMinSize.y, backgroundMinSize.y, minimumSize.y})};
	}
	
	sf::Vector2f LayerWithConstCenter::getNormalSize() {
		sf::Vector2f objectNormalSize {object->getNormalSize()};
		sf::Vector2f backgroundNormalSize {background->getNormalSize()};
		objectNormalSize = sf::Vector2f{std::max(objectNormalSize.x, objectNormalSize.y * aspectRatio), std::max(objectNormalSize.y, objectNormalSize.x / aspectRatio)};
		return {std::max(objectNormalSize.x, backgroundNormalSize.x), std::max(objectNormalSize.y, backgroundNormalSize.y)};
	}
	
	void LayerWithConstCenter::update() {
		object->update();
	}
	
	void LayerWithConstCenter::copy(LayerWithConstCenter *layerWithConstCenter) {
		ILayer::copy(layerWithConstCenter);
		layerWithConstCenter->sizeOffset = this->sizeOffset;
	}
	
	LayerWithConstCenter *LayerWithConstCenter::copy() {
		LayerWithConstCenter* layerWithConstCenter{new LayerWithConstCenter{object->copy(), background->copy(), aspectRatio, minimumSize}};
		LayerWithConstCenter::copy(layerWithConstCenter);
		return layerWithConstCenter;
	}
}
