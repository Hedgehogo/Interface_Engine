#pragma once

#include "../interactiveSimple.h"
#include "../../../../../layout/layout.h"
#include "../../../../../../drawable/iDrawable/iDrawable.h"

#include "../../../onlyDrawable/onlyDrawable.h"

namespace ui{
    class Switch : public Interactive_Simple, public Layout, public IDrawable{
    protected:
        DrawManager activeDrawManager;
        DrawManager inactiveDrawManager;

        OnlyDrawable* activeBackground;
        OnlyDrawable* inactiveBackground;
        bool active;

    public:
        Switch(OnlyDrawable *inactiveBackground, OnlyDrawable *activeBackground, sf::Mouse::Button button = sf::Mouse::Button::Left, bool startActive = false);

        void init(sf::RenderTarget &renderTarget, DrawManager& drawManager, PanelManager &panelManager) override;

        void switchValue();

        void setPosition(sf::Vector2f position) override;

        void move(sf::Vector2f position) override;

        void setSize(sf::Vector2f size) override;

        sf::Vector2f getMinSize() override;

        sf::Vector2f getNormalSize() override;

        void draw() override;

        void resize(sf::Vector2f size, sf::Vector2f position) override;

        Switch* copy() override;

        void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;

        ~Switch();
    };
}