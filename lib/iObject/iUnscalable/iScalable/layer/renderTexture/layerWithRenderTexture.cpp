#include "layerWithRenderTexture.h"
#include <cmath>

namespace ui {
	void LayerWithRenderTexture::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) {
		this->renderTarget = &renderTarget;
		this->interactionManager = &interactionManager;
		drawManager.add(*this);
		object->init(renderTexture, this->drawManager, interactionManager, interactionStack, panelManager);
	}
	
	LayerWithRenderTexture::LayerWithRenderTexture(IScalable *object, bool optimize, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObject(object), optimize(optimize), active(true), renderTarget(nullptr), interactionManager(nullptr) {
		sprite.setScale({1, -1});
	}
	
	void LayerWithRenderTexture::draw() {
		if(!optimize || active || interactionManager->isBlocked()) {
			renderTexture.clear(sf::Color(0, 0, 0, 0));
			drawManager.draw();
			active = false;
		}
		renderTarget->draw(sprite);
	}
	
	void LayerWithRenderTexture::resize(sf::Vector2f size, sf::Vector2f position) {
		active = true;
		sf::Vector2i start {static_cast<int>(std::floor(position.x)), static_cast<int>(std::ceil(position.y))};
		sf::Vector2i end {static_cast<int>(std::floor(position.x + size.x)), static_cast<int>(std::ceil(position.y + size.y))};
		Layer::resize(static_cast<sf::Vector2f>(end - start), static_cast<sf::Vector2f>(start));
		renderTexture.create(static_cast<unsigned>(end.x), static_cast<unsigned>(end.y));
		
		sprite.setTextureRect(sf::IntRect({start.x, 0}, end - start));
		sprite.setTexture(renderTexture.getTexture());
		sprite.setPosition(static_cast<sf::Vector2f>(sf::Vector2i{start.x, end.y}));
		
		object->resize(size, position);
	}
	
	bool LayerWithRenderTexture::updateInteractions(sf::Vector2f mousePosition) {
		active = true;
		return object->updateInteractions(mousePosition);
	}
	
	sf::Vector2f LayerWithRenderTexture::getMinSize() {
		return max(object->getMinSize(), minimumSize);
	}
	
	void LayerWithRenderTexture::copy(LayerWithRenderTexture *layerWithRenderTexture) {
		layerWithRenderTexture->renderTarget = this->renderTarget;
		sf::Vector2u size = this->renderTexture.getSize();
		layerWithRenderTexture->renderTexture.create(size.x, size.y);
	}
	
	LayerWithRenderTexture *LayerWithRenderTexture::copy() {
		LayerWithRenderTexture* layerWithRenderTexture{new LayerWithRenderTexture{object->copy(), optimize}};
		LayerWithRenderTexture::copy(layerWithRenderTexture);
		return layerWithRenderTexture;
	}
	
	void LayerWithRenderTexture::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        object->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
}