#include "layerWithConstCenter.h"

namespace ui {
	void LayerWithConstCenter::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		object->init(renderTarget, interactionStack, interactionManager, panelManager);
		background->init(renderTarget, interactionStack, interactionManager, panelManager);
	}
	
	LayerWithConstCenter::LayerWithConstCenter(IScalable* object, IDrawable* background, float aspectRatio, sf::Vector2f minSize) :
		ILayer(minSize), LayoutWithObject(object), LayoutWithBackground(background), aspectRatio(aspectRatio) {}
	
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
		object->resize(size, position + (this->size - size) / 2.0f);
	}
	
	bool LayerWithConstCenter::updateInteractions(sf::Vector2f mousePosition) {
		if(object->inArea(mousePosition)) {
			return object->updateInteractions(mousePosition);
		}
		return background->updateInteractions(mousePosition);
	}
	
	sf::Vector2f LayerWithConstCenter::getMinSize() {
		sf::Vector2f objectMinSize {object->getMinSize()};
		objectMinSize = sf::Vector2f{std::max(objectMinSize.x, objectMinSize.y * aspectRatio), std::max(objectMinSize.y, objectMinSize.x / aspectRatio)};
		return max(objectMinSize, background->getMinSize(), minimumSize);
	}
	
	sf::Vector2f LayerWithConstCenter::getNormalSize() {
		sf::Vector2f objectNormalSize {object->getNormalSize()};
		objectNormalSize = sf::Vector2f{std::max(objectNormalSize.x, objectNormalSize.y * aspectRatio), std::max(objectNormalSize.y, objectNormalSize.x / aspectRatio)};
		return max(objectNormalSize, background->getNormalSize());
	}
	
	LayerWithConstCenter *LayerWithConstCenter::copy() {
		LayerWithConstCenter* layerWithConstCenter{new LayerWithConstCenter{object->copy(), background->copy(), aspectRatio, minimumSize}};
		ILayer::copy(layerWithConstCenter);
		return layerWithConstCenter;
	}
	
	void LayerWithConstCenter::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
        object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
}
