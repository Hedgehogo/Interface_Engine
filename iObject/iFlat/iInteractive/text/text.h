#pragma once

#include <vector>

#include "../simple/interactiveSimple.h"
#include "indivisible/baseIndivisible.h"
#include "textBlock/baseTextBlock.h"
#include "../../iDrawn/iDrawn.h"

namespace ui {
	class Text : public IInteractive {
    public:
        enum class Align{
            left,
            right,
            center
        };
    protected:
        sf::RenderWindow *window;

        sf::Vector2f minSize;

        bool interact;
        bool oldInteract;
        IInteraction* oldInteraction;
        Align align;

        uint size;
        uint lineSpacing;

        sf::Vector2f textSize;

        std::vector<ui::BaseIndivisible*> textIndivisibleBlocks;
        ui::IDrawn *background;
        void init(sf::RenderWindow &window, Panel *parent, PanelStack &overlayStack);
    public:

        Text(std::vector<ui::BaseTextBlock *> textBlocks, IDrawn *background, int size = 14, uint lineSpacing = 14, sf::Font *font = nullptr, Align align = Align::left);

        void update() override;

        bool updateInteractions(sf::Vector2f mousePosition) override;

        void draw() override;

        void resize(sf::Vector2f size, sf::Vector2f position) override;

        void resizeLeft(sf::Vector2f startRender, sf::Vector2f endRender);
        void resizeRight(sf::Vector2f startRender, sf::Vector2f endRender);
        void resizeCenter(sf::Vector2f startRender, sf::Vector2f endRender);

        sf::Vector2f getTextSize();

        sf::Vector2f getMinSize() override;

        sf::Vector2f getNormalSize() override;

        ~Text();
    };
}
