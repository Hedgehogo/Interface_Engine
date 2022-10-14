#pragma once

#include <vector>

#include "../interactive.h"
#include "character/baseCharacter.h"
#include "textBlock/baseTextBlock.h"
#include "../../iScalable/uninteractive/uninteractive.hpp"
#include "resizer/baseResizer.h"
#include "resizer/simple/resizer.h"
#include "../../iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp"
#include "event/selection/textSelectionEvent.hpp"
#include "../../../../enums/keyHandler/keyHandler.hpp"
#include "interaction/buttons/textButtonsInteraction.hpp"
#include "event/copy/textCopyEvent.hpp"
#include "interaction/buttons/textButtonsInteraction.hpp"
#include "interaction/empty/textEmptyInteraction.hpp"

namespace ui {
	class Text : public Interactive, public IScalable, public IDrawable, public IUpdatable {
    protected:
        sf::RenderTarget *renderTarget;

        bool interact;
        bool oldInteract;

        TextInteraction* selectionInteraction;
        TextInteraction* copyInteraction;
        TextInteraction* textInteraction;

        struct Selection {
            std::vector<BaseCharacter*>::iterator start;
            std::vector<BaseCharacter*>::iterator end;
        } selection;


        uint size;

        std::vector<BaseCharacter*> textCharacters;
        std::vector<BaseTextBlock*> textBocks;
        std::vector<BaseLine* > lines;

        BaseResizer* resizer;
		
        IUninteractive *background;
		
        void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, IPanelManager &panelManager);

    public:
        Text(std::vector<BaseTextBlock *> textBlocks, IUninteractive *background = new FullColor(sf::Color::White), int size = 14, sf::Font *font = nullptr, sf::Color textColor = sf::Color::Black,
             sf::Color textSelectionColor = sf::Color::White, sf::Color backgroundSelectionColor = sf::Color::Blue, sf::Color inactiveTextSelectionColor = nullColor,
             sf::Color inactiveBackgroundSelectionColor = {150, 150, 150}, BaseResizer *resizer = new Resizer{1.15, BaseResizer::Align::left},
             TextInteraction *textInteraction = new TextEmptyInteraction{},
             TextInteraction *selectionInteraction = new TextButtonsInteraction{new TextSelectionEvent{}, {KeyHandler::Key::mouseLeft}},
             TextInteraction *copyInteraction = new TextButtonsInteraction{new TextCopyEvent{}, {KeyHandler::Key::lControl, KeyHandler::Key::c}});

        ~Text();

        void setSelection(Selection selection);
		
        void setSelectionStart(std::vector<BaseCharacter*>::iterator start);
		
        void setSelectionEnd(std::vector<BaseCharacter*>::iterator end);
		
        Selection getSelection() const;
		
        std::vector<BaseCharacter *>::iterator getSelectionStart() const;
		
        std::vector<BaseCharacter *>::iterator getSelectionEnd() const;

        std::u32string getSelectionText();

        std::vector<BaseCharacter *>::iterator getCharacter(sf::Vector2f mousePosition);

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
        Text(std::vector<BaseTextBlock *> textBlocks, IUninteractive *background, uint size, BaseResizer *resizer, sf::RenderTarget *renderTarget,
             TextInteraction* textInteraction, TextInteraction *copyInteraction, TextInteraction *selectionInteraction);
		
    public:
        Text *copy() override;

        void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
    };
	
	bool convertPointer(const YAML::Node &node, Text *&text);

    extern std::vector<BaseCharacter *>::iterator nullBaseCharacterIterator;
}
