#include <iostream>
#include <cmath>
#include "text.h"

ui::Text::Text(std::vector<ui::BaseTextBlock *> textBlocks, ui::IDrawable *background, int size, float lineSpacing, sf::Font *font
    , sf::Color textColor, sf::Color textSelectionColor, sf::Color backgroundSelectionColor, ui::Text::Align align) :
    background(background), align(align), size(size), lineSpacing(lineSpacing), textBocks(textBlocks), startRender({0, 0}), endRender(0, 0){
    for (ui::BaseTextBlock* textBlock : textBlocks) {
        textBlock->setTextVariables(textColor, textSelectionColor, backgroundSelectionColor, font, size);
        std::vector<ui::BaseCharacter*> characters = textBlock->getCharacters();
        textCharacters.insert(textCharacters.end(), characters.begin(), characters.end());
    }


}

ui::Text::~Text() {
    for (ui::BaseCharacter*& textCharacter : textCharacters) {
        delete textCharacter;
    }
    for (ui::BaseTextBlock*& textBlock : textBocks) {
        delete textBlock;
    }
    delete background;
}

void ui::Text::init(sf::RenderTarget &renderTarget, ui::PanelManager &panelManager) {
    this->renderTarget = &renderTarget;
    for (BaseTextBlock * textBlock : textBocks) {
        textBlock->init(renderTarget, *interactionStack, *interactionManager, panelManager);
    }
    IObject::initObject(background, renderTarget, *interactionStack, *interactionManager, panelManager);
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
    for (ui::BaseCharacter *character : textCharacters) {
        character->draw();
    }
}

void ui::Text::move(sf::Vector2f position) {
    startRender += position;
    endRender += position;

    background->move(position);
    for (BaseCharacter*& character : textCharacters) {
        character->move(position);
    }
}

void ui::Text::setPosition(sf::Vector2f position) {
    background->setPosition(position);
    for (BaseCharacter*& character : textCharacters) {
        character->move({position - startRender});
    }

    endRender += position - startRender;
    startRender = position;
}

void ui::Text::printCharacter(ui::BaseCharacter *character, float kerning) {
    character->setPosition(nextPosition);
    nextPosition.x += character->getAdvance() + kerning;
    distanceEnter++;
}

float ui::Text::equalize(uint i) {
    float lineSize = 0;
    for (int j = i - distanceEnter; j < i; ++j) {
        float characterSize = textCharacters[j]->getHeight();
        if(lineSize < characterSize)
            lineSize = characterSize;
    }
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
    return lineSize;
}

void ui::Text::porting(int i) {
    float lineSize = equalize(i);
    nextPosition.y += lineSize * lineSpacing;
    nextPosition.x = startRender.x;

    distanceEnter = 0;
}

void ui::Text::autoPorting(int i) {

    distanceEnter -= distanceSpace;
    porting(i - distanceSpace);

    for (uint j = i - distanceSpace; j < i; ++j) {
        float kerning;
        if (j < i - 1)
            kerning = textCharacters[j]->getKerning(textCharacters[j + 1]->getChar());
        printCharacter(textCharacters[j], kerning);
    }

    distanceEnter = distanceSpace;
    distanceSpace = 0;
}
void ui::Text::resize(sf::Vector2f size, sf::Vector2f position) {
    background->resize(size, position);
    if(size.x == endRender.x - startRender.x){
        for (BaseCharacter*& character : textCharacters) {
            character->move({position - startRender});
        }
        startRender = position;
        endRender = position + size;
        return;
    }
    startRender = position;
    endRender = position + size;
    this->nextPosition = startRender;

    for (int i = 0; i < textCharacters.size(); i++) {
        ui::BaseCharacter* character = textCharacters[i];

        float kerning = 0;

        ui::BaseCharacter::Special specialText = character->isSpecial();

        switch (specialText) {
            case BaseCharacter::Special::no:
                printCharacter(character, kerning);
                distanceSpace++;
                break;
            case BaseCharacter::Special::space:
                if (this->nextPosition.x <= endRender.x){
                    printCharacter(character, kerning);
                    distanceSpace = 0;
                } else{
                    autoPorting(i);
                    printCharacter(character, kerning);
                }
                break;
            case BaseCharacter::Special::enter:
                if (this->nextPosition.x > endRender.x)
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
}

sf::Vector2f ui::Text::getAreaPosition() {
	return startRender;
}

sf::Vector2f ui::Text::getAreaSize() {
	return endRender - startRender;
}

sf::Vector2f ui::Text::getMinSize() {

    sf::Vector2f minSize = {0, 0};
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

    sf::Vector2f backgroundMinSize{background->getMinSize()};
    return sf::Vector2f{std::max(minSize.x, backgroundMinSize.x), std::max(minSize.y, backgroundMinSize.y)};
}

sf::Vector2f ui::Text::getNormalSize() {
    sf::Vector2f normalSize = background->getNormalSize();
    sf::Vector2f minSize = getMinSize();
    return {std::max(normalSize.x, minSize.x), std::max(normalSize.y, minSize.y)};
}

ui::Text::Text(std::vector<ui::BaseTextBlock *> textBlocks, ui::IDrawable *background, uint size, float lineSpacing, ui::Text::Align align) :
    textBocks(textBlocks), background(background), size(size), lineSpacing(lineSpacing), align(align){
    for (ui::BaseTextBlock* textBlock : textBlocks) {
        std::vector<ui::BaseCharacter*> characters = textBlock->getCharacters();
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

void ui::Text::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
    for (BaseCharacter*& character : textCharacters) {
        character->drawDebug(renderTarget, indentAddition, hue + hueOffset, hueOffset);
    }

    background->drawDebug(renderTarget, indent, indentAddition, hue + hueOffset, hueOffset);
}

