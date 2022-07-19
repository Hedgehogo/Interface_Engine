#include "layerWithRenderTexture.h"
#include <cmath>

namespace ui {
	void LayerWithRenderTexture::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		this->renderTarget = &renderTarget;
		this->interactionManager = &interactionManager;
		initObject(object, renderTexture, interactionStack, interactionManager, panelManager);
	}
	
	void LayerWithRenderTexture::copy(LayerWithRenderTexture *layerWithRenderTexture) {
		layerWithRenderTexture->renderTarget = this->renderTarget;
		sf::Vector2u size = this->renderTexture.getSize();
		layerWithRenderTexture->renderTexture.create(size.x, size.y);
	}
	
	LayerWithRenderTexture::LayerWithRenderTexture(IScalable *object, bool optimize, sf::Vector2f minSize) :
		ILayer(minSize), object(object), optimize(optimize), active(true), renderTarget(nullptr), interactionManager(nullptr) {
		sprite.setScale({1, -1});
	}
	
	LayerWithRenderTexture::~LayerWithRenderTexture() {
		delete object;
	}
	
	void LayerWithRenderTexture::draw() {
		if(!optimize || active || interactionManager->isBlocked()) {
			renderTexture.clear(sf::Color(0, 0, 0, 0));
			object->draw();
			active = false;
		}
		renderTarget->draw(sprite);
	}
	
	void LayerWithRenderTexture::resize(sf::Vector2f size, sf::Vector2f position) {
		active = true;
		sf::Vector2i start {static_cast<int>(std::floor(position.x)), static_cast<int>(std::ceil(position.y))};
		sf::Vector2i end {static_cast<int>(std::floor(position.x + size.x)), static_cast<int>(std::ceil(position.y + size.y))};
		ILayer::resize(static_cast<sf::Vector2f>(end - start), static_cast<sf::Vector2f>(start));
		renderTexture.create(static_cast<unsigned>(end.x), static_cast<unsigned>(end.y));
		
		sprite.setTextureRect(sf::IntRect({start.x, 0}, end - start));
		sprite.setTexture(renderTexture.getTexture());
		sprite.setPosition(static_cast<sf::Vector2f>(sf::Vector2i{start.x, end.y}));
		
		object->resize(size, position);
	}
	
	void LayerWithRenderTexture::update() {
		object->update();
	}
	
	bool LayerWithRenderTexture::updateInteractions(sf::Vector2f mousePosition) {
		active = true;
		return object->updateInteractions(mousePosition);
	}
	
	sf::Vector2f LayerWithRenderTexture::getMinSize() {
		sf::Vector2f objectMinSize{object->getMinSize()};
		return {std::max(objectMinSize.x, minimumSize.x), std::max(objectMinSize.y, minimumSize.y)};
	}
	
	sf::Vector2f LayerWithRenderTexture::getNormalSize() {
		return object->getNormalSize();
	}
	
	LayerWithRenderTexture *LayerWithRenderTexture::copy() {
		LayerWithRenderTexture* layerWithRenderTexture{new LayerWithRenderTexture{object->copy()}};
		LayerWithRenderTexture::copy(layerWithRenderTexture);
		return layerWithRenderTexture;
	}
	
	void LayerWithRenderTexture::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        object->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
}