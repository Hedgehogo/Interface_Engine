#include <iostream>
#include <cmath>
#include <vector>

#include "text.h"

#include "../../../../../modules/appendix/yaml-cpp/fileBuffer/fileBuffer.hpp"

namespace ui {
    std::vector<BaseCharacter *>::iterator nullBaseCharacterIterator{nullptr};

    Text::Text(std::vector<BaseTextBlock *> textBlocks, IUninteractive *background, int size, sf::Font *font, sf::Color textColor, sf::Color textSelectionColor, sf::Color backgroundSelectionColor,
               sf::Color inactiveTextSelectionColor, sf::Color inactiveBackgroundSelectionColor, BaseResizer *resizer, TextInteraction *textInteraction, TextInteraction *selectionInteraction,
               TextInteraction *copyInteraction) :
        background(background), size(size), textBocks(textBlocks), resizer(resizer),
        selectionInteraction(selectionInteraction), copyInteraction(copyInteraction), textInteraction(textInteraction) {
        for (BaseTextBlock *textBlock: textBlocks) {
            textBlock->setTextVariables(textColor, textSelectionColor, backgroundSelectionColor, (inactiveTextSelectionColor == nullColor ? textColor : inactiveTextSelectionColor), inactiveBackgroundSelectionColor, font,
                                        size);
            std::vector<BaseCharacter *> characters = textBlock->getCharacters();
            textCharacters.insert(textCharacters.end(), characters.begin(), characters.end());
        }
        resizer->init(textCharacters, lines);
        copyInteraction->init(this);
        selectionInteraction->init(this);
        textInteraction->init(this);
    }

    Text::~Text() {
        for (BaseLine *&line: lines) {
            delete line;
        }
        for (BaseCharacter *&textCharacter: textCharacters) {
            delete textCharacter;
        }
        for (BaseTextBlock *&textBlock: textBocks) {
            delete textBlock;
        }
        delete background;
        delete resizer;
        delete textInteraction;
        delete copyInteraction;
        delete selectionInteraction;
    }

    void Text::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, IPanelManager &panelManager) {
        updateManager.add(*this);
        this->renderTarget = &renderTarget;
        background->init(renderTarget, drawManager, updateManager, *interactionManager, *interactionStack, panelManager);
        for (BaseTextBlock *textBlock: textBocks) {
            textBlock->init(renderTarget, drawManager, updateManager, *interactionManager, *interactionStack, panelManager);
        }
        drawManager.add(*this);
    }

    void Text::setSelection(Text::Selection selection) {
        this->selection = selection;
    }

    void Text::setSelectionStart(std::vector<BaseCharacter *>::iterator start) {
        selection.start = start;
    }

    void Text::setSelectionEnd(std::vector<BaseCharacter *>::iterator end) {
        selection.end = end;
    }

    Text::Selection Text::getSelection() const {
        return selection;
    }

    std::vector<BaseCharacter *>::iterator Text::getSelectionStart() const {
        return selection.start;
    }

    std::vector<BaseCharacter *>::iterator Text::getSelectionEnd() const {
        return selection.end;
    }

    std::u32string Text::getSelectionText() {
        if (selection.start != nullBaseCharacterIterator && selection.end != nullBaseCharacterIterator) {
            std::u32string SelectionText{};
            std::vector<BaseCharacter *>::iterator localStart;
            std::vector<BaseCharacter *>::iterator localEnd;
            if (std::distance(selection.start, selection.end) < 0) {
                localStart = selection.end;
                localEnd = selection.start;
            } else {
                localStart = selection.start;
                localEnd = selection.end;
            }
            SelectionText.resize(std::distance(localStart, localEnd));

            for (int i = 0; i < SelectionText.length(); ++i) {
                SelectionText[i] = (*(localStart + i))->getChar();
            }

            return SelectionText;
        }
        return std::u32string{U""};
    }

    float getDistanceY(std::vector<BaseCharacter *>::iterator iterator, float mousePositionY) {
        return std::min(std::abs(mousePositionY - (*iterator)->getPosition().y), std::abs(mousePositionY - ((*iterator)->getPosition().y - (*iterator)->getHeight())));
    }

    bool minDistanceX(std::vector<BaseCharacter *>::iterator &a, std::vector<BaseCharacter *>::iterator &b, float find) {
        float distanceToA{std::abs((*a)->getPosition().x - find)},
            distanceToA1{std::abs((*a)->getPosition().x + (*a)->getAdvance() - find)},
            distanceToB{std::abs((*b)->getPosition().x - find)},
            distanceToB1{std::abs((*b)->getPosition().x + (*b)->getAdvance() - find)};
        if (distanceToA > distanceToA1)
            std::swap(distanceToA, distanceToA1);
        if (distanceToB > distanceToB1)
            std::swap(distanceToB, distanceToB1);

        if (distanceToA == distanceToB)
            return distanceToA1 < distanceToB1;
        else
            return distanceToA < distanceToB;
    }


    std::vector<BaseCharacter *>::iterator Text::getCharacter(sf::Vector2f mousePosition) {
        std::vector<BaseCharacter *>::iterator result{nullptr};


        for (auto iterator = textCharacters.begin(); iterator != textCharacters.end(); ++iterator) {
            if (result != nullBaseCharacterIterator) {
                float DistanceYToIterator{getDistanceY(iterator, mousePosition.y)};
                float DistanceYToResult{getDistanceY(result, mousePosition.y)};
                if (DistanceYToIterator <= DistanceYToResult) {
                    if (DistanceYToIterator < DistanceYToResult) {
                        result = iterator;
                    }
                    if (minDistanceX(iterator, result, mousePosition.x)) {
                        result = iterator;
                    }
                }
            } else {
                result = iterator;
            }
        }

        if (mousePosition.x > (*result)->getPosition().x + (static_cast<float>((*result)->getSizeTexture().x) / 2.f)) {
            ++result;
        }

        return result;
    }

    void Text::update() {
        if (interact != oldInteract) {
            oldInteract = interact;
            bool unNull = selection.start != nullBaseCharacterIterator && selection.end != nullBaseCharacterIterator;
            if (unNull && std::distance(selection.start, selection.end) < 0) {
                std::swap(selection.start, selection.end);
            }

            if (interact) {
                interactionManager->addInteraction(*selectionInteraction);
                interactionManager->addInteraction(*copyInteraction);
                interactionManager->addInteraction(*textInteraction);

                if (unNull) {
                    for (auto item = selection.start; item != selection.end; ++item) {
                        (*item)->setActive(true);
                    }
                }
            } else {
                interactionManager->deleteInteraction(*textInteraction);
                interactionManager->deleteInteraction(*copyInteraction);
                interactionManager->deleteInteraction(*selectionInteraction);

                if (unNull) {
                    for (auto item = selection.start; item != selection.end; ++item) {
                        (*item)->setActive(false);
                    }
                }
            }
        }
        interact = false;


        for (BaseTextBlock *textBlock: textBocks) {
            textBlock->update();
        }
    }

    bool Text::updateInteractions(sf::Vector2f mousePosition) {
        interact = true;

        for (BaseTextBlock *textBock: textBocks) {

            if (textBock->in(mousePosition))
                if (textBock->updateInteractions(mousePosition))
                    return true;
        }
        return background->updateInteractions(mousePosition);
    }

    void Text::draw() {
        for (BaseCharacter *character: textCharacters) {
            character->draw();
        }

        for (BaseLine *&line: lines) {
            line->draw();
        }
    }

    void Text::move(sf::Vector2f position) {
        background->move(position);
        resizer->move(position);
    }

    void Text::setPosition(sf::Vector2f position) {
        background->setPosition(position);
        resizer->setPosition(position);
    }

    void Text::resize(sf::Vector2f size, sf::Vector2f position) {
        background->resize(size, position);

        resizer->resize(size, position);
    }

    sf::Vector2f Text::getAreaPosition() {
        return background->getAreaPosition();
    }

    sf::Vector2f Text::getAreaSize() {
        return background->getAreaSize();
    }

    sf::Vector2f Text::getMinSize() {
        return max(resizer->getMinSize(), background->getMinSize());
    }

    sf::Vector2f Text::getNormalSize() {
        return max(resizer->getNormalSize(), background->getNormalSize());
    }

    Text::Text(std::vector<BaseTextBlock *> textBlocks, IUninteractive *background, uint size, BaseResizer *resizer, sf::RenderTarget *renderTarget, TextInteraction *textInteraction, TextInteraction *copyInteraction, TextInteraction *selectionInteractio) :
        textBocks(textBlocks), background(background), size(size), resizer(resizer), renderTarget(renderTarget),
        selectionInteraction(selectionInteraction), copyInteraction(copyInteraction), textInteraction(textInteraction){
        for (BaseTextBlock *textBlock: textBlocks) {
            std::vector<BaseCharacter *> characters = textBlock->getCharacters();
            textCharacters.insert(textCharacters.end(), characters.begin(), characters.end());
        }
        resizer->init(textCharacters, lines);
        copyInteraction->init(this);
        selectionInteraction->init(this);
        textInteraction->init(this);
    }

    Text *Text::copy() {
        std::vector<BaseTextBlock *> copyTextBlocks;
        for (BaseTextBlock *textBlock: textBocks) {
            copyTextBlocks.push_back(textBlock->copy());
        }

        return new Text{copyTextBlocks, background->copy(), size, resizer->copy(), renderTarget, textInteraction->copy(), copyInteraction->copy(), selectionInteraction->copy()};
    }

    bool convertPointer(const YAML::Node &node, Text *&text) {
        std::vector<BaseTextBlock *> textBlocks;
        IUninteractive *background;
        int size{14};
        sf::Font *font{nullptr};
        sf::Color textColor{sf::Color::Black};
        sf::Color textSelectionColor{sf::Color::White};
        sf::Color backgroundSelectionColor{sf::Color::Blue};
        sf::Color inactiveTextSelectionColor = nullColor;
        sf::Color inactiveBackgroundSelectionColor = {150, 150, 150};
        BaseResizer *resizer;
        TextInteraction* selectionInteraction;
        TextInteraction* copyInteraction;
        TextInteraction* textInteraction;

        if (node["text-block"]) {
            BaseTextBlock *textBlock;
            node["text-block"] >> textBlock;
            textBlocks.push_back(textBlock);
        } else if (node["text-blocks"]) {
            for (const YAML::Node &textBlockNode: node["text-blocks"]) {
                BaseTextBlock *textBlock;
                textBlockNode >> textBlock;
                textBlocks.push_back(textBlock);
            }
        } else {
            throw YAML::BadConversion{node["text-blocks"].Mark()};
        }

        if (node["background"]) node["background"] >> background;
        else background = new FullColor(sf::Color::White);

        if (node["selection-interaction"]) node["selection-interaction"] >> selectionInteraction;
        else selectionInteraction = new TextButtonsInteraction{new TextSelectionEvent{}, {Key::mouseLeft}};

        if (node["copy-interaction"]) node["copy-interaction"] >> copyInteraction;
        else copyInteraction = new TextButtonsInteraction{new TextCopyEvent{}, {Key::lControl, Key::c}};

        if (node["text-interaction"]) node["text-interaction"] >> textInteraction;
        else textInteraction = new TextEmptyInteraction{};

        if (node["resizer"]) node["resizer"] >> resizer;
        else resizer = new Resizer{1.15, BaseResizer::Align::left};

        if (node["size"]) node["size"] >> size;
        if (node["font"]) node["font"] >> font;
        if (node["text-color"]) node["text-color"] >> textColor;
        if (node["text-selection-color"]) node["text-selection-color"] >> textSelectionColor;
        if (node["background-selection-color"]) node["background-selection-color"] >> backgroundSelectionColor;
        if (node["inactive-text-selection-color"]) node["inactive-text-selection-color"] >> inactiveTextSelectionColor;
        if (node["inactive-background-selection-color"]) node["inactive-background-selection-color"] >> inactiveBackgroundSelectionColor;

        text = new Text{textBlocks, background, size, font, textColor, textSelectionColor, backgroundSelectionColor, inactiveTextSelectionColor, inactiveBackgroundSelectionColor, resizer, textInteraction, selectionInteraction, copyInteraction};
		return true;
    }

    void Text::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        for (BaseCharacter *&character: textCharacters) {
            character->drawDebug(renderTarget, indentAddition, hue + hueOffset, hueOffset);
        }

        background->drawDebug(renderTarget, indent, indentAddition, hue + hueOffset, hueOffset);
    }
}