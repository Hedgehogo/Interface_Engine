#include <iostream>
#include <cmath>

#include "text.h"

#include "../../../../../yaml/yamlWithSfml/fileBuffer/fileBuffer.hpp"
#include "../../../../interaction/iInteraction/oneButton/oneButtonInteraction.hpp"

ui::Text::Text(std::vector<ui::BaseTextBlock *> textBlocks, IUninteractive *background, int size, sf::Font *font, sf::Color textColor, sf::Color textSelectionColor, sf::Color backgroundSelectionColor,
               sf::Color inactiveTextSelectionColor, sf::Color inactiveBackgroundSelectionColor, BaseResizer *resizer, Key button) :
    background(background), size(size), textBocks(textBlocks), resizer(resizer), textEvent(*this), interaction(new OneButtonInteraction{&textEvent, button}){
    for (ui::BaseTextBlock* textBlock : textBlocks) {
        textBlock->setTextVariables(textColor, textSelectionColor, backgroundSelectionColor, (inactiveTextSelectionColor == nullColor ? textColor : inactiveTextSelectionColor), inactiveBackgroundSelectionColor, font, size);
        std::vector<ui::BaseCharacter*> characters = textBlock->getCharacters();
        textCharacters.insert(textCharacters.end(), characters.begin(), characters.end());
    }
    resizer->init(textCharacters, lines);
}

ui::Text::~Text() {
    for (ui::BaseLine*& line : lines) {
        delete line;
    }
    for (ui::BaseCharacter*& textCharacter : textCharacters) {
        delete textCharacter;
    }
    for (ui::BaseTextBlock*& textBlock : textBocks) {
        delete textBlock;
    }
    delete background;
}

void ui::Text::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, PanelManager &panelManager) {
    updateManager.add(*this);
    this->renderTarget = &renderTarget;
	background->init(renderTarget, drawManager, updateManager, *interactionManager, *interactionStack, panelManager);
    for (BaseTextBlock * textBlock : textBocks) {
		textBlock->init(renderTarget, drawManager, updateManager, *interactionManager, *interactionStack, panelManager);
    }
    drawManager.add(*this);
}

std::u32string ui::Text::getSelectionText() {
    return textEvent.getSelectionText();
}

float getDistanceY(std::vector<ui::BaseCharacter *>::iterator iterator, float mousePositionY){
    return std::min(std::abs(mousePositionY - (*iterator)->getPosition().y), std::abs(mousePositionY - ((*iterator)->getPosition().y - (*iterator)->getHeight())));
}

bool minDistanceX(std::vector<ui::BaseCharacter *>::iterator& a, std::vector<ui::BaseCharacter *>::iterator& b, float find){
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

std::vector<ui::BaseCharacter *>::iterator nullBaseCharacterIterator{nullptr};

std::vector<ui::BaseCharacter *>::iterator ui::Text::getCharacter(sf::Vector2f mousePosition) {
    std::vector<ui::BaseCharacter *>::iterator result{nullptr};

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

    if(mousePosition.x > (*result)->getPosition().x + (static_cast<float>((*result)->getSizeTexture().x) / 2.f)){
        ++result;
    }

    return result;
}

void ui::Text::update() {
    if (interact != oldInteract) {
        oldInteract = interact;
        auto start = textEvent.getStart();
        auto end = textEvent.getEnd();
        bool unNull = start != nullBaseCharacterIterator && end != nullBaseCharacterIterator;
        if (unNull && std::distance(start, end) < 0) {
            std::swap(start, end);
        }

        if (interact) {
            interactionManager->addInteraction(*interaction);

            if (unNull) {
                for (auto item = start; item != end; ++item) {
                    (*item)->setActive(true);
                }
            }
        } else {
            interactionManager->deleteInteraction(*interaction);

            if (unNull) {
                for (auto item = start; item != end; ++item) {
                    (*item)->setActive(false);
                }
            }
        }
    }
    interact = false;


    for (ui::BaseTextBlock *textBlock: textBocks) {
        textBlock->update();
    }
}

bool ui::Text::updateInteractions(sf::Vector2f mousePosition) {
    interact = true;

    for (ui::BaseTextBlock* textBock : textBocks) {

        if (textBock->in(mousePosition))
            if (textBock->updateInteractions(mousePosition))
                return true;
    }
    return background->updateInteractions(mousePosition);
}

void ui::Text::draw() {
    for (char32_t ch : getSelectionText() ) {
        std::cout << static_cast<char>(ch);
    }
    std::cout << std::endl;
    for (ui::BaseCharacter *character : textCharacters) {
        character->draw();
    }

    for (BaseLine*& line : lines) {
        line->draw();
    }
}

void ui::Text::move(sf::Vector2f position) {
    background->move(position);
    resizer->move(position);
}

void ui::Text::setPosition(sf::Vector2f position) {
    background->setPosition(position);
    resizer->setPosition(position);
}

void ui::Text::resize(sf::Vector2f size, sf::Vector2f position) {
    background->resize(size, position);

    resizer->resize(size, position);
}

sf::Vector2f ui::Text::getAreaPosition() {
	return background->getAreaPosition();
}

sf::Vector2f ui::Text::getAreaSize() {
	return background->getAreaSize();
}

sf::Vector2f ui::Text::getMinSize() {
    return max(resizer->getMinSize(), background->getMinSize());
}

sf::Vector2f ui::Text::getNormalSize() {
    return max(resizer->getNormalSize(), background->getNormalSize());
}

ui::Text::Text(std::vector<ui::BaseTextBlock *> textBlocks, IUninteractive *background, uint size, BaseResizer *resizer, sf::RenderTarget *renderTarget) :
    textBocks(textBlocks), background(background), size(size), resizer(resizer), renderTarget(renderTarget), textEvent(*this){
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

    return new Text{copyTextBlocks, background->copy(), size, resizer->copy(), renderTarget};
}

ui::Text *ui::Text::createFromYaml(const YAML::Node &node) {
    std::vector<ui::BaseTextBlock *> textBlocks;
    IUninteractive *background;
    int size{14};
    sf::Font *font{nullptr};
    sf::Color textColor{sf::Color::Black};
    sf::Color textSelectionColor{sf::Color::White};
    sf::Color backgroundSelectionColor{sf::Color::Blue};
    sf::Color inactiveTextSelectionColor = nullColor;
    sf::Color inactiveBackgroundSelectionColor = {150, 150, 150};
    BaseResizer *resizer;
    Key key = Key::mouseLeft;

    if (node["text-block"]){
        BaseTextBlock* textBlock;
        node["text-block"] >> textBlock;
        textBlocks.push_back(textBlock);
    } else if (node["text-blocks"]){
        for (const YAML::Node& textBlockNode : node["text-blocks"]) {
            BaseTextBlock* textBlock;
            textBlockNode >> textBlock;
            textBlocks.push_back(textBlock);
        }
    } else {
        throw YAML::BadConversion{node["text-blocks"].Mark()};
    }

    if (node["background"]) node["background"] >> background;
    else background = new ui::FullColor(sf::Color::White);

    if (node["resizer"]) node["resizer"] >> resizer;
    else resizer = new Resizer{1.15, BaseResizer::Align::left};

    if (node["size"]) node["size"] >> size;
    if (node["font"]) node["font"] >> font;
    if (node["text-color"]) node["text-color"] >> textColor;
    if (node["text-selection-color"]) node["text-selection-color"] >> textSelectionColor;
    if (node["background-selection-color"]) node["background-selection-color"] >> backgroundSelectionColor;
    if (node["inactive-text-selection-color"]) node["inactive-text-selection-color"] >> inactiveTextSelectionColor;
    if (node["inactive-background-selection-color"]) node["inactive-background-selection-color"] >> inactiveBackgroundSelectionColor;
    if (node["key"]) key = createKeyFromYaml(node["key"]);

    return new Text{textBlocks, background, size, font, textColor, textSelectionColor, backgroundSelectionColor, inactiveTextSelectionColor, inactiveBackgroundSelectionColor, resizer, key};
}

void ui::Text::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
    for (BaseCharacter*& character : textCharacters) {
        character->drawDebug(renderTarget, indentAddition, hue + hueOffset, hueOffset);
    }

    background->drawDebug(renderTarget, indent, indentAddition, hue + hueOffset, hueOffset);
}