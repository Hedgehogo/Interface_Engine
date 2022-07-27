#include "layerWithBackground.h"

namespace ui {
    LayerWithBackground::LayerWithBackground(IScalable *object, OnlyDrawable *background, sf::Vector2f offset, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObject(object), LayoutWithBackground(background), offset(offset) {}

    void LayerWithBackground::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) {
		background->init(renderTarget, drawManager, interactionManager, interactionStack, panelManager);
		object->init(renderTarget, drawManager, interactionManager, interactionStack, panelManager);
    }

    void LayerWithBackground::setPosition(sf::Vector2f position) {
        background->setPosition(position);
        object->setPosition(position);
    }

    void LayerWithBackground::move(sf::Vector2f position) {
        background->move(position);
        object->move(position);
    }

    void LayerWithBackground::setSize(sf::Vector2f size) {
        background->setSize(size);
        object->setSize(size);
    }

    sf::Vector2f LayerWithBackground::getMinSize() {
        return max(object->getMinSize() + offset * 2.f, background->getMinSize(), minimumSize);
    }

    sf::Vector2f LayerWithBackground::getNormalSize() {
        return max(object->getNormalSize() + offset * 2.f, background->getNormalSize());
    }

    void LayerWithBackground::resize(sf::Vector2f size, sf::Vector2f position) {
        Layer::resize(size, position);

        background->resize(size, position);
        object->resize(size - offset * 2.f, position + offset);
    }

    void LayerWithBackground::update() {
        background->update();
        object->update();
    }

    bool LayerWithBackground::updateInteractions(sf::Vector2f mousePosition) {
        return object->updateInteractions(mousePosition);
    }

    LayerWithBackground *LayerWithBackground::copy() {
        return new LayerWithBackground(object->copy(), background->copy(), offset, minimumSize);
    }

    void LayerWithBackground::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
        object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);

    }

}