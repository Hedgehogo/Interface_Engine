#include "layerWithBackground.h"

namespace ui {
    LayerWithBackground::LayerWithBackground(IObject *object, IDrawable *background, sf::Vector2f minSize) : ILayer(minSize), object(object), background(background) {}

    void LayerWithBackground::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
        background->init(renderTarget, interactionStack, interactionManager, panelManager);
        object->init(renderTarget, interactionStack, interactionManager, panelManager);
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
        sf::Vector2f minSizeObject = object->getMinSize();
        sf::Vector2f minSizeBackground = background->getMinSize();

        return {std::max(minimumSize.x, std::max(minSizeObject.x, minSizeBackground.x)), std::max(minimumSize.y, std::max(minSizeObject.y, minSizeBackground.y))};
    }

    sf::Vector2f LayerWithBackground::getNormalSize() {
        sf::Vector2f normalSizeObject = object->getNormalSize();
        sf::Vector2f normalSizeBackground = background->getNormalSize();
        return {std::max(normalSizeObject.x, normalSizeBackground.x), std::max(normalSizeObject.y, normalSizeBackground.y)};
    }

    void LayerWithBackground::draw() {
        background->draw();
        object->draw();
    }

    void LayerWithBackground::resize(sf::Vector2f size, sf::Vector2f position) {
        ILayer::resize(size, position);

        background->resize(size, position);
        object->resize(size, position);
    }

    void LayerWithBackground::update() {
        background->update();
        object->update();
    }

    bool LayerWithBackground::updateInteractions(sf::Vector2f mousePosition) {
        return object->updateInteractions(mousePosition);
    }

    LayerWithBackground *LayerWithBackground::copy() {
        return new LayerWithBackground(object->copy(), background->copy(), minimumSize);
    }

    void LayerWithBackground::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
        object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);

    }

}