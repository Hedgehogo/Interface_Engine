#include <iostream>
#include "text.h"

ui::Text::Text(std::vector<ui::BaseTextBlock *> textBlocks, ui::IDrawn *background, int size, float lineSpacing, sf::Font *font
               , sf::Color textColor, sf::Color textSelectionColor, sf::Color backgroundSelectionColor, ui::Text::Align align) :
    background(background), align(align), size(size), lineSpacing(lineSpacing), textBocks(textBlocks){
    for (ui::BaseTextBlock* textBlock : textBlocks) {
        textBlock->setTextVariables(textColor, textSelectionColor, backgroundSelectionColor, font, size);
        std::vector<ui::BaseCharacter*> characters = textBlock->character();
        textCharacters.insert(textCharacters.end(), characters.begin(), characters.end());
    }

    float wordSizeX = 0;

    for (ui::BaseCharacter *character : textCharacters) {
        if (character->isSpecial() == BaseCharacter::Special::space){
            if (minSize.x < wordSizeX)
                minSize.x = wordSizeX;
            wordSizeX = 0;
        }else{
            wordSizeX += character->getAdvance();
        }
    }
}

ui::Text::~Text() {
    for (ui::BaseCharacter* textCharacter : textCharacters) {
        delete textCharacter;
    }
    for (ui::BaseTextBlock* textBlock : textBocks) {
        delete textBlock;
    }
    delete background;
}

void ui::Text::init(sf::RenderWindow &window, ui::Panel *parent, ui::PanelStack &overlayStack) {
    this->window = &window;
    for (ui::BaseCharacter* character : textCharacters) {
        character->init(window);
    }
    for (BaseTextBlock * textBlock : textBocks) {
        textBlock->init(*interactionManager, *interactionStack);
    }
    IObject::initObject(background, window, *interactionStack, *interactionManager, parent, overlayStack);
}

void ui::Text::update() {
    for (ui::BaseTextBlock* textBlock : textBocks) {
        textBlock->update();
    }
}

bool ui::Text::updateInteractions(sf::Vector2f mousePosition) {
    for (ui::BaseTextBlock* textBock : textBocks) {

        if (textBock->in(mousePosition))
            if (textBock->updateInteractions(mousePosition))
                return true;
    }
    return false;
}

void ui::Text::draw() {
    background->draw();
    for (ui::BaseCharacter *indivisible : textCharacters) {
        indivisible->draw();
    }
}

void ui::Text::printCharacter(sf::Vector2f &position, ui::BaseCharacter* character) {
    character->setPosition(position);
    position.x += character->getAdvance();
    if (lineSize < character->getHeight())
        lineSize = character->getHeight();
    distanceEnter++;
}

void ui::Text::equalize(uint i) {
    for (uint j = i - distanceEnter; j < i; ++j) {
        textCharacters[j]->move({0, lineSize});
    }
}

void ui::Text::autoPorting(sf::Vector2f &position, int i, float startRenderX) {

    porting(position, i, startRenderX);

    for (uint j = i - distanceSpace; j < i; ++j) {
        printCharacter(position, textCharacters[j]);
    }

    distanceEnter = distanceSpace;
    distanceSpace = 0;
}

void ui::Text::porting(sf::Vector2f &position, int i, float startRenderX) {
    equalize(i);
    position.y += lineSize * lineSpacing;
    position.x = startRenderX;

    distanceEnter = 0;
    lineSize = 0;
}

void ui::Text::resize(sf::Vector2f size, sf::Vector2f position) {
    background->resize(size, position);

    sf::Vector2f startRender = position;
    sf::Vector2f endRender = position + size;
    position = startRender;

    for (int i = 0; i < textCharacters.size(); i++) {
        ui::BaseCharacter* character = textCharacters[i];

        float kerning = 0;
        if (i < textCharacters.size() - 1)
            kerning = character->getKerning(textCharacters[i + 1]->getChar());

        ui::BaseCharacter::Special specialText = character->isSpecial();

        switch (specialText) {
            case BaseCharacter::Special::no:
                printCharacter(position, character);
                distanceSpace++;
                break;
            case BaseCharacter::Special::space:
                if (position.x< endRender.x){
                    printCharacter(position, character);
                    distanceSpace = 0;
                } else{
                    distanceEnter++;
                    distanceSpace++;
                    autoPorting(position, i + 1, startRender.x);
                }
                break;
            case BaseCharacter::Special::enter:
                distanceSpace++;
                distanceEnter++;
                porting(position, i + 1, startRender.x);
                break;
        }
    }

    if (endRender.x < position.x){
        autoPorting(position, textCharacters.size(), startRender.x);
    }
    equalize(textCharacters.size());

    distanceEnter = 0;
    distanceSpace = 0;
    lineSize = 0;
}

sf::Vector2f ui::Text::getMinSize() {
    return minSize;
}

sf::Vector2f ui::Text::getNormalSize() {
    return sf::Vector2f();
}

ui::Text::Text(std::vector<ui::BaseTextBlock *> textBlocks, ui::IDrawn *background, uint size, float lineSpacing, ui::Text::Align align) :
    textBocks(textBlocks), background(background), size(size), lineSpacing(lineSpacing), align(align){
    for (ui::BaseTextBlock* textBlock : textBlocks) {
        std::vector<ui::BaseCharacter*> characters = textBlock->character();
        textCharacters.insert(textCharacters.end(), characters.begin(), characters.end());
    }
}

ui::Text *ui::Text::copy() {
    std::vector<BaseTextBlock *> copyTextBlocks;
    for (BaseTextBlock * textBlock : textBocks) {
        copyTextBlocks.push_back(textBlock->copy());
    }

    return new Text{copyTextBlocks, background->copy(), size, lineSpacing, align};
}
