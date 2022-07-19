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
        sf::RenderTarget *renderTarget;

        Align align;

        uint size;
        float lineSpacing;

        sf::Vector2f textSize;

        std::vector<ui::BaseCharacter*> textCharacters;
        std::vector<BaseTextBlock*> textBocks;

        ui::IDrawn *background;
        void init(sf::RenderTarget &renderTarget, PanelManager &panelManager);
		
    public:
        Text(std::vector<ui::BaseTextBlock *> textBlocks, IDrawn *background = new ui::FullColor(sf::Color::White),
             int size = 14, float lineSpacing = 1.15, sf::Font *font = nullptr,
             sf::Color textColor = sf::Color(0, 0, 0), sf::Color textSelectionColor = sf::Color(0, 0, 0),
             sf::Color backgroundSelectionColor = sf::Color(0, 0, 0), Align align = Align::left);

        ~Text();

        void update() override;

        bool updateInteractions(sf::Vector2f mousePosition) override;

        void draw() override;

        void move(sf::Vector2f position);

        void setPosition(sf::Vector2f position);

    private:
        uint distanceEnter = 0;
        uint distanceSpace = 0;

        sf::Vector2f nextPosition;

        sf::Vector2f startRender;
        sf::Vector2f endRender;

        void printCharacter(ui::BaseCharacter *character, float kerning);

        void porting(int i);
        void autoPorting(int i);

        float equalize(uint i);

    public:
        void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getAreaPosition() override;
		
		sf::Vector2f getAreaSize() override;

        sf::Vector2f getMinSize() override;

        sf::Vector2f getNormalSize() override;
		
    protected:
        Text(std::vector<ui::BaseTextBlock *> textBlocks, IDrawn *background = new ui::FullColor(sf::Color::White), uint size = 14, float lineSpacing = 1.15, ui::Text::Align align = Align::left);
		
    public:
        Text *copy() override;

        void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
    };
}
