#pragma once

#include "SFML/Graphics.hpp"

#include "../layer.h"
#include "../../onlyDrawable/onlyDrawable.h"
#include "../../../../layout/object/layoutWithObject.h"
#include "../../../../layout/background/layoutWithBackground.h"

namespace ui {
    class LayerWithBackground : public Layer, public LayoutWithBackground, public LayoutWithObject {
    protected:
        sf::Vector2f offset;
		
    public:
        LayerWithBackground(IScalable *object, OnlyDrawable* background, sf::Vector2f offset = {0, 0}, sf::Vector2f minSize = {0, 0});

        void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;

        void setPosition(sf::Vector2f position);

        void move(sf::Vector2f position);

        void setSize(sf::Vector2f size);

        sf::Vector2f getMinSize() override;

        sf::Vector2f getNormalSize() override;

        void resize(sf::Vector2f size, sf::Vector2f position) override;

        void update() override;

        bool updateInteractions(sf::Vector2f mousePosition) override;

        LayerWithBackground* copy() override;

        void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset);

    };
}