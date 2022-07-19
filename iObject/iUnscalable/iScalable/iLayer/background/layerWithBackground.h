#pragma once

#include "SFML/Graphics.hpp"

#include "../iLayer.h"
#include "../../iDrawable/iDrawable.h"

namespace ui {
    class LayerWithBackground : public ILayer {
    private:
        IObject* object;
        IDrawable* background;
    public:
        LayerWithBackground(IObject* object, IDrawable* background, sf::Vector2f minSize = {0, 0});

        void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;

        void setPosition(sf::Vector2f position);

        void move(sf::Vector2f position);

        void setSize(sf::Vector2f size);

        sf::Vector2f getMinSize() override;

        sf::Vector2f getNormalSize() override;

        void draw() override;

        void resize(sf::Vector2f size, sf::Vector2f position) override;

        void update() override;

        bool updateInteractions(sf::Vector2f mousePosition) override;

        LayerWithBackground* copy() override;

        void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset);

    };
}