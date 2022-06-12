#include "text.h"

ui::Text::Text(std::vector<ui::BaseTextBlock *> textBlocks, IDrawn *background, int size, uint lineSpacing, sf::Font *font, Align align) :
    background(background), align(align), size(size), lineSpacing(lineSpacing){
    for (ui::BaseTextBlock* textBlock : textBlocks) {
        textBlock->setTextVariables(lineSpacing, size, font);
        std::vector<ui::BaseIndivisible*> indivisibles = textBlock->divide();
        textIndivisibleBlocks.insert(textIndivisibleBlocks.end(), indivisibles.begin(), indivisibles.end());

        for (ui::BaseIndivisible* indivisible : indivisibles) {
            if (minSize.x < indivisible->getSize().x)
                minSize.x = indivisible->getSize().x;
        }
    }
}

void ui::Text::init(sf::RenderWindow &window, ui::Panel *parent, ui::PanelStack &overlayStack) {
    this->window = &window;
    for (ui::BaseIndivisible* textBlock : textIndivisibleBlocks) {
        textBlock->init(window);
    }
    IObject::initObject(background, window, *interactionStack, *interactionManager, parent, overlayStack);
}

void ui::Text::update() {
    if(interact != oldInteract) {
        oldInteract = interact;
        if(interact) {

        } else {
            //interactionManager->deleteInteraction(*oldInteraction);
        }
    }
    interact = false;
}

bool ui::Text::updateInteractions(sf::Vector2f mousePosition) {
    interact = true;
    return true;
}

void ui::Text::draw() {
    background->draw();
    for (ui::BaseIndivisible *indivisible : textIndivisibleBlocks) {
        indivisible->draw();
    }
}

void ui::Text::resize(sf::Vector2f size, sf::Vector2f position) {
    sf::Vector2f startPosition = position;
    sf::Vector2f endPosition = position + size;
    switch (align) {
        case Align::left:
            resizeLeft(startPosition, endPosition);
            break;
        case Align::right:
            resizeRight(startPosition, endPosition);
            break;
        case Align::center:
            resizeCenter(startPosition, endPosition);
            break;
    }
}

void ui::Text::resizeLeft(sf::Vector2f startRender, sf::Vector2f endRender) {
    sf::Vector2f position = startRender;
    int distanceSpase = 0;
    for (int i = 0; i < textIndivisibleBlocks.size(); i++) {
        ui::BaseIndivisible* indivisible = textIndivisibleBlocks[i];
        ui::BaseIndivisible::special specialText = indivisible->isSpecial();
        switch (specialText) {
            case BaseIndivisible::special::no:
                indivisible->setPosition(position);
                position.x += indivisible->getSize().x;
                distanceSpase++;
                break;
            case BaseIndivisible::special::spase:
                if (position.x < endRender.x){
                    indivisible->setPosition(position);
                    position.x += indivisible->getSize().x;
                    distanceSpase = 0;
                } else{
                    position.x = startRender.x;
                    position.y += size + lineSpacing;

                    for (int j = i - distanceSpase; j < i; ++j) {
                        indivisible = textIndivisibleBlocks[j];
                        indivisible->setPosition(position);
                        position.x += indivisible->getSize().x;
                    }

                    indivisible = textIndivisibleBlocks[i];
                    indivisible->setPosition(position);
                    position.x += indivisible->getSize().x;

                    distanceSpase = 0;
                }
                break;
            case BaseIndivisible::special::enter:
                position.x = startRender.x;
                position.y += size + lineSpacing;
                distanceSpase = 0;
                break;
        }
    }
}

void ui::Text::resizeRight(sf::Vector2f startRender, sf::Vector2f endRender) {

}

void ui::Text::resizeCenter(sf::Vector2f startRender, sf::Vector2f endRender) {

}

sf::Vector2f ui::Text::getMinSize() {
    return minSize;
}

sf::Vector2f ui::Text::getNormalSize() {
    return sf::Vector2f();
}

ui::Text::~Text() {
    for (ui::BaseIndivisible* textBlock : textIndivisibleBlocks) {
        delete textBlock;
    }
}
