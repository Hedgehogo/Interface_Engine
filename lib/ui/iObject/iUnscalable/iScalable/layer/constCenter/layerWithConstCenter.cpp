#include "layerWithConstCenter.hpp"

namespace ui {
	void LayerWithConstCenter::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) {
		background->init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
		object->init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
		drawManager.add(*this);
		firstObject->init(renderTarget, this->firstDrawManager, updateManager, interactionManager, interactionStack, panelManager);
		secondObject->init(renderTarget, this->secondDrawManager, updateManager, interactionManager, interactionStack, panelManager);
	}
	
	LayerWithConstCenter::LayerWithConstCenter(IScalable* object, IUninteractive* background, float aspectRatio, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObject(object), LayoutWithBackground(background), LayoutWithTwoObjects(new Empty, new Empty), aspectRatio(aspectRatio) {}

	LayerWithConstCenter::LayerWithConstCenter(IScalable *object, IScalable *firstObject, IScalable *secondObject, IUninteractive *background, float aspectRatio, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObject(object), LayoutWithBackground(background), LayoutWithTwoObjects(firstObject, secondObject), aspectRatio(aspectRatio) {}
	
	void LayerWithConstCenter::setAspectRatio(float aspectRatio) {
		this->aspectRatio = aspectRatio;
		this->setPosition(position);
	}

	void LayerWithConstCenter::draw()
	{
		if ( renderFirst ) firstDrawManager.draw();
		if ( renderSecond ) secondDrawManager.draw();
	}

	void LayerWithConstCenter::resize(sf::Vector2f size, sf::Vector2f position) {
		Layer::resize(size, position);

		sf::Vector2f firstMinSize { firstObject->getMinSize() };
		sf::Vector2f secondMinSize { secondObject->getMinSize() };
		sf::Vector2f secondPosition { position };
		sf::Vector2f objectsSize { size };

		background->resize(size, position);
		float sizeAspectRatio = size.x / size.y;
		if(sizeAspectRatio > aspectRatio) {
			size.x = size.y * aspectRatio;
			objectsSize.x = (this->size.x - size.x) / 2.0f;
			secondPosition.x += objectsSize.x + size.x;
		} else {
			size.y = size.x / aspectRatio;
			objectsSize.y = (this->size.y - size.y) / 2.0f;
			secondPosition.y += objectsSize.y + size.y;
		}
		renderFirst = firstMinSize.x < objectsSize.x && firstMinSize.y < objectsSize.y;
		renderSecond = secondMinSize.x < objectsSize.x && secondMinSize.y < objectsSize.y;

		object->resize(size, position + (this->size - size) / 2.0f);

		if (renderFirst) firstObject->resize(objectsSize, position);
		if (renderSecond) secondObject->resize(objectsSize, secondPosition);
	}
	
	bool LayerWithConstCenter::updateInteractions(sf::Vector2f mousePosition) {
		if(object->inArea(mousePosition)) {
			return object->updateInteractions(mousePosition);
		}
		if (renderFirst && firstObject->inArea(mousePosition)) {
			return firstObject->updateInteractions(mousePosition);
		}
		if (renderSecond && secondObject->inArea(mousePosition)) {
			return secondObject->updateInteractions(mousePosition);
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
		LayerWithConstCenter* layerWithConstCenter{new LayerWithConstCenter{object->copy(), firstObject->copy(), secondObject->copy(), background->copy(), aspectRatio, minimumSize}};
		Layer::copy(layerWithConstCenter);
		return layerWithConstCenter;
	}
	
	bool convertPointer(const YAML::Node &node, LayerWithConstCenter *&layerWithConstCenter) {
		IScalable *object;
		IScalable *firstObject;
		IScalable *secondObject;
		float aspectRatio;
		IUninteractive *background{};
		sf::Vector2f minSize{};
		
		node["object"] >> object;
		if (node["first-object"]) {
			node["first-object"] >> firstObject;
		} else {
			firstObject = new Empty{};
		}
		if (node["second-object"]) {
			node["second-object"] >> secondObject;
		} else {
			secondObject = new Empty{};
		}
		node["aspect-ratio"] >> aspectRatio;
		if(node["background"]) {
			node["background"] >> background;
		} else {
			background = new Empty{};
		}
		if(node["min-size"])
			node["min-size"] >> minSize;
		
		{ layerWithConstCenter = new LayerWithConstCenter{object, firstObject, secondObject, background, aspectRatio, minSize}; return true; }
	}
	
	void LayerWithConstCenter::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
        object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		firstObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		secondObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}

}
