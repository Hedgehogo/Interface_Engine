#pragma once

#include <vector>

#include "../simple/interactiveSimple.h"
#include "character/baseCharacter.h"
#include "textBlock/baseTextBlock.h"
#include "../../iDrawn/iDrawn.h"
#include "../../iDrawn/fullColor/fullColor.h"

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

        sf::Vector2f minSize{0, 0};

        Align align;

        uint size;
        float lineSpacing;

        sf::Vector2f textSize;

        std::vector<ui::BaseCharacter*> textCharacters;
        std::vector<BaseTextBlock*> textBocks;

        ui::IDrawn *background;
        void init(sf::RenderWindow &window, Panel *parent, PanelStack &overlayStack);
    public:

        Text(std::vector<ui::BaseTextBlock *> textBlocks, IDrawn *background = new ui::FullColor(sf::Color::White),
             int size = 14, float lineSpacing = 1.15, sf::Font *font = nullptr,
             sf::Color textColor = sf::Color(0, 0, 0), sf::Color textSelectionColor = sf::Color(0, 0, 0),
             sf::Color backgroundSelectionColor = sf::Color(0, 0, 0), Align align = Align::left);

        ~Text();

        void update() override;

        bool updateInteractions(sf::Vector2f mousePosition) override;

        void draw() override;

    private:
        uint distanceEnter = 0;
        uint distanceSpace = 0;

        float lineSize = 0;

        void printCharacter(sf::Vector2f &position, ui::BaseCharacter* character);

        void porting(sf::Vector2f &position, int i, float startRenderX);
        void autoPorting(sf::Vector2f &position, int i, float startRenderX);

        void equalize(uint i);
    public:

        void resize(sf::Vector2f size, sf::Vector2f position) override;

        sf::Vector2f getMinSize() override;

        sf::Vector2f getNormalSize() override;
    protected:
        Text(std::vector<ui::BaseTextBlock *> textBlocks, IDrawn *background = new ui::FullColor(sf::Color::White), uint size = 14, float lineSpacing = 1.15, ui::Text::Align align = Align::left);
    public:
        Text *copy() override;
    };
}
