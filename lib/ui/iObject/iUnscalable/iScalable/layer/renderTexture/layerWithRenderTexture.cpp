#include "layerWithRenderTexture.hpp"

namespace ui {
	void LayerWithRenderTexture::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) {
		this->renderTarget = &renderTarget;
		this->interactionManager = &interactionManager;
		drawManager.add(*this);
		object->init(renderTexture, this->drawManager, updateManager, interactionManager, interactionStack, panelManager);
	}
	
	LayerWithRenderTexture::LayerWithRenderTexture(IScalable *object, bool optimize, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObject(object), optimize(optimize), active(true), renderTarget(nullptr), interactionManager(nullptr){}
	
	void LayerWithRenderTexture::draw() {
		if(!optimize || active || interactionManager->isBlocked()) {
			renderTexture.clear(sf::Color(0, 0, 0, 0));
			drawManager.draw();
            sprite.setTexture(renderTexture.getTexture());
			active = false;
		}
		renderTarget->draw(sprite);
	}
	
	void LayerWithRenderTexture::resize(sf::Vector2f size, sf::Vector2f position) {
        Layout::resize(size, position);
        active = true;

        sf::Vector2i start {static_cast<int>(std::floor(position.x)), static_cast<int>(std::ceil(position.y))};
        sf::Vector2i end {static_cast<int>(std::floor(position.x + size.x)), static_cast<int>(std::ceil(position.y + size.y))};
        
        sf::Vector2i textureSize{end - start};

        view.reset({sf::Vector2f{sf::Vector2i{start.x, start.y + textureSize.y}}, sf::Vector2f{sf::Vector2i{textureSize.x, -textureSize.y}}});

        renderTexture.create(textureSize.x, textureSize.y);
        renderTexture.setView(view);

		sprite.setTexture(renderTexture.getTexture());
        sprite.setTextureRect({{0, 0}, textureSize});
		sprite.setPosition(sf::Vector2f{start});

		object->resize(size, position);
	}
	
	bool LayerWithRenderTexture::updateInteractions(sf::Vector2f mousePosition) {
		active = true;
		return object->updateInteractions(mousePosition);
	}
	
	sf::Vector2f LayerWithRenderTexture::getMinSize() {
		return max(object->getMinSize(), minimumSize, {1, 1});
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
	
	LayerWithRenderTexture *LayerWithRenderTexture::createFromYaml(const YAML::Node &node) {
		IScalable* object;
		bool optimize{true};
		sf::Vector2f minSize{0, 0};
		node["object"] >> object;
        if (node["optimize"]) node["optimize"] >> optimize;
        if (node["min-size"]) node["min-size"] >> minSize;
		return new LayerWithRenderTexture{object, optimize, minSize};
	}
}