#include "layerWithRenderTexture.h"

namespace ui {
	void LayerWithRenderTexture::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		this->renderTarget = &renderTarget;
		initObject(object, renderTexture, interactionStack, interactionManager, panelManager);
	}
	
	void LayerWithRenderTexture::copy(LayerWithRenderTexture *layerWithRenderTexture) {
		layerWithRenderTexture->renderTarget = this->renderTarget;
		sf::Vector2u size = this->renderTexture.getSize();
		layerWithRenderTexture->renderTexture.create(size.x, size.y);
	}
	
	LayerWithRenderTexture::LayerWithRenderTexture(IFlat *object, sf::Vector2f minSize) : ILayer(minSize), object(object), renderTarget(nullptr) {
		sprite.setScale({1, -1});
	}
	
	LayerWithRenderTexture::~LayerWithRenderTexture() {
		delete object;
	}
	
	void LayerWithRenderTexture::draw() {
		object->draw();
		sprite.setTexture(renderTexture.getTexture());
		sprite.setPosition({position.x, position.y + size.y});
		renderTarget->draw(sprite);
	}
	
	void LayerWithRenderTexture::resize(sf::Vector2f size, sf::Vector2f position) {
		ILayer::resize(size, position);
		
		renderTexture.create(static_cast<unsigned>(size.x), static_cast<unsigned>(size.y));
		sprite.setTextureRect(sf::IntRect({0, 0}, static_cast<sf::Vector2i>(size)));
		
		object->resize(size, {0, 0});
	}
	
	void LayerWithRenderTexture::update() {
		object->update();
	}
	
	bool LayerWithRenderTexture::updateInteractions(sf::Vector2f mousePosition) {
		return object->updateInteractions(mousePosition - position);
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
}