#pragma once

#include "../uninteractive.hpp"

namespace ui {
    class OnlyDrawable : public IUninteractive, public IDrawable{
    protected:
        sf::RenderTarget *renderTarget;

        void copy(OnlyDrawable* OnlyDrawable);

    public:
        OnlyDrawable();

        void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) override;

        bool updateInteractions(sf::Vector2f mousePosition) override;

        void draw() override = 0;

        void resize(sf::Vector2f size, sf::Vector2f position) override = 0;

        sf::Vector2f getMinSize() override = 0;

        sf::Vector2f getNormalSize() override = 0;

        OnlyDrawable* copy() override = 0;
    };
}