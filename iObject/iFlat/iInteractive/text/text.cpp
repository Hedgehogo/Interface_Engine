#include <iostream>
#include <cmath>
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
        if (character->isSpecial() == BaseCharacter::Special::no){
            wordSizeX += character->getAdvance();
        }else{
            if (minSize.x < wordSizeX)
                minSize.x = wordSizeX;
            wordSizeX = 0;
        }
    }
    if (minSize.x < wordSizeX)
        minSize.x = wordSizeX;
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

void ui::Text::init(sf::RenderTarget &renderTarget, ui::PanelManager &overlayStack) {
    this->renderTarget = &renderTarget;
    for (ui::BaseCharacter* character : textCharacters) {
        character->init(renderTarget);
    }
    for (BaseTextBlock * textBlock : textBocks) {
        textBlock->init(*interactionManager, *interactionStack);
    }
    IObject::initObject(background, renderTarget, *interactionStack, *interactionManager, overlayStack);
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
    return background->updateInteractions(mousePosition);
}

void ui::Text::draw() {
    background->draw();
    for (ui::BaseCharacter *indivisible : textCharacters) {
        indivisible->draw();
    }
}

void ui::Text::printCharacter(ui::BaseCharacter* character) {
    character->setPosition(nextPosition);
    nextPosition.x += character->getAdvance();
    if (lineSize < character->getHeight())
        lineSize = character->getHeight();
    distanceEnter++;
}

void ui::Text::equalize(uint i) {
    sf::Vector2f offset{endRender.x - (textCharacters[i - 1]->getPosition().x), lineSize};
    if (textCharacters[i - 1]->isSpecial() != BaseCharacter::Special::space)
        offset.x -= textCharacters[i - 1]->getAdvance();

    switch (align) {
        case Align::left:
            offset.x = 0;
            break;
        case Align::center:
            offset.x /= 2;
            break;
    }

    for (uint j = i - distanceEnter; j < i; ++j) {
        textCharacters[j]->move(offset);
    }
}

void ui::Text::porting(int i) {
    equalize(i);
    nextPosition.y += lineSize * lineSpacing;
    nextPosition.x = startRender.x;

    distanceEnter = 0;
    lineSize = 0;
}

void ui::Text::autoPorting(int i) {

    distanceEnter -= distanceSpace;
    porting(i - distanceSpace);

    for (uint j = i - distanceSpace; j < i; ++j) {
        printCharacter(textCharacters[j]);
    }

    distanceEnter = distanceSpace;
    distanceSpace = 0;
}

void ui::Text::resize(sf::Vector2f size, sf::Vector2f position) {
    background->resize(size, position);

    startRender = position;
    endRender = position + size;
    this->nextPosition = startRender;

    for (int i = 0; i < textCharacters.size(); i++) {
        ui::BaseCharacter* character = textCharacters[i];

/*
        float kerning = 0;
        if (i < textCharacters.createSize() - 1)
            kerning = character->getKerning(textCharacters[i + 1]->getChar());
*/

        ui::BaseCharacter::Special specialText = character->isSpecial();

        switch (specialText) {
            case BaseCharacter::Special::no:
                printCharacter(character);
                distanceSpace++;
                break;
            case BaseCharacter::Special::space:
                if (this->nextPosition.x < endRender.x){
                    printCharacter(character);
                    distanceSpace = 0;
                } else{
                    autoPorting(i);
                    printCharacter(character);
                }
                break;
            case BaseCharacter::Special::enter:

                if (lineSize < character->getHeight())
                    lineSize = character->getHeight();

                if (this->nextPosition.x >= endRender.x)
                    autoPorting(i);
                porting(i);
                break;
        }
    }

    if (endRender.x < this->nextPosition.x){
        autoPorting(textCharacters.size());
    }
    equalize(textCharacters.size());

    distanceEnter = 0;
    distanceSpace = 0;
    lineSize = 0;
}

sf::Vector2f ui::Text::getPosition() {
	return startRender;
}

sf::Vector2f ui::Text::getAreaSize() {
	return endRender - startRender;
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
