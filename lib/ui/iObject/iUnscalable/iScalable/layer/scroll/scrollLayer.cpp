#include "scrollLayer.hpp"
#include <iostream>

namespace ui {
	ScrollLayer::ScrollLayer(IUnscalable *object, const PSRVec2f &normalObjectPosition, const sf::Vector2f &minSize) :
		ILayerWithView(minSize), object(object), normalObjectPosition(normalObjectPosition){
		normalObjectPosition->addSetter([&](sf::Vector2f vec){
			this->object->setPosition(getNewObjectPosition(vec));
		});
		setRangeBounds(normalObjectPosition, {0, 0}, {1, 1});
	}

	void ScrollLayer::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) {
		ILayerWithView::init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
		object->init(renderTarget, this->drawManager, updateManager, interactionManager, interactionStack, panelManager);
	}

	sf::Vector2f ScrollLayer::getMinSize() {
		return max(minimumSize, object->getMinSize());
	}

	sf::Vector2f ScrollLayer::getNormalSize() {
		return object->getNormalSize();
	}

	sf::Vector2f ScrollLayer::getNewObjectPosition(sf::Vector2f normalObjectPosition) {
		sf::Vector2f maxOffset{object->getSize() - size};
		sf::Vector2f offset{maxOffset * normalObjectPosition};
		return position - offset;
	}

	void ScrollLayer::resize(sf::Vector2f size, sf::Vector2f position) {
		ILayerWithView::resize(size, position);

		object->setSize(size);

		sf::Vector2f objectSize{object->getSize()};
		if (objectSize.x == size.x && objectSize.y == size.y)
			return object->setPosition(position);
		object->setPosition(getNewObjectPosition(normalObjectPosition->getValue()));
	}

	bool ScrollLayer::updateInteractions(sf::Vector2f mousePosition) {
		return object->updateInteractions(mousePosition);
	}

	ScrollLayer *ScrollLayer::copy() {
		return new ScrollLayer{object->copy(), normalObjectPosition, minimumSize};
	}

	ScrollLayer::~ScrollLayer() {
		delete object;
	}

	bool convertPointer(const YAML::Node &node, ScrollLayer *&scrollLayer){
		scrollLayer = new ScrollLayer{
			node["object"].as<IUnscalable*>(),
			Buffer::get<SRVec2f>(node["normal-object-position"]),
			(node["min-size"] ? node["min-size"].as<sf::Vector2f>() : sf::Vector2f{0, 0})
		};
		return true;
	}
} // ui