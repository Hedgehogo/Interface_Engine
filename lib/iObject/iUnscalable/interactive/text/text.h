#pragma once

#include <vector>

#include "../interactive.h"
#include "character/baseCharacter.h"
#include "textBlock/baseTextBlock.h"
#include "../../iScalable/onlyDrawable/onlyDrawable.h"
#include "../../iScalable/onlyDrawable/fullColor/fullColor.h"
#include "resizer/baseResizer.h"
#include "resizer/simple/resizer.h"

namespace ui {
	class Text : public Interactive, public IScalable, public IDrawable, public IUpdatable {
    protected:
        sf::RenderTarget *renderTarget;

        uint size;

        sf::Vector2f textSize;

        std::vector<ui::BaseCharacter*> textCharacters;
        std::vector<BaseTextBlock*> textBocks;
        std::vector<BaseLine* > lines;

        BaseResizer* resizer;


        ui::OnlyDrawable *background;
        void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, PanelManager &panelManager);
		
    public:
        Text(std::vector<ui::BaseTextBlock *> textBlocks, OnlyDrawable *background = new ui::FullColor(sf::Color::White), int size = 14, sf::Font *font = nullptr, sf::Color textColor = sf::Color(0, 0, 0),
             sf::Color textSelectionColor = sf::Color(0, 0, 0), sf::Color backgroundSelectionColor = sf::Color(0, 0, 0), BaseResizer *resizer = new Resizer{1.15, BaseResizer::Align::left});

        ~Text();

        void update() override;

        bool updateInteractions(sf::Vector2f mousePosition) override;

        void draw() override;

        void move(sf::Vector2f position);

        void setPosition(sf::Vector2f position);

        void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getAreaPosition() override;
		
		sf::Vector2f getAreaSize() override;

        sf::Vector2f getMinSize() override;

        sf::Vector2f getNormalSize() override;
		
    protected:
        Text(std::vector<ui::BaseTextBlock *> textBlocks, OnlyDrawable *background = new ui::FullColor(sf::Color::White), uint size = 14, BaseResizer *resizer = new Resizer(1.15, Resizer::Align::left));
		
    public:
        Text *copy() override;

        void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
    };
}
