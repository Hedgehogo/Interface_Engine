#include <iostream>
#include "text.h"
#include "../../../../../yaml/yamlWithSfml/buffer/buffer.hpp"

ui::Text::Text(std::vector<ui::BaseTextBlock *> textBlocks, IUninteractive *background, int size, sf::Font *font, sf::Color textColor, sf::Color textSelectionColor, sf::Color backgroundSelectionColor, BaseResizer *resizer) :
    background(background), size(size), textBocks(textBlocks), resizer(resizer){
    for (ui::BaseTextBlock* textBlock : textBlocks) {
        textBlock->setTextVariables(textColor, textSelectionColor, backgroundSelectionColor, font, size);
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
    textBocks(textBlocks), background(background), size(size), resizer(resizer), renderTarget(renderTarget){
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
    sf::Color textSelectionColor{sf::Color::Black};
    sf::Color backgroundSelectionColor{sf::Color::Black};
    BaseResizer *resizer;

    if (node["text-block"]){
        BaseTextBlock* textBlock;
        node["text-block"] >> textBlock;
        textBlocks.push_back(textBlock);
    } else if (node["text-blocks"]){
        for (const YAML::Node& textBlockNode : node["text-blocks"]) {
            BaseTextBlock* textBlock;
            node["text-block"] >> textBlock;
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

    return new Text{textBlocks, background, size, font, textColor, textSelectionColor, backgroundSelectionColor, resizer};
}

void ui::Text::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
    for (BaseCharacter*& character : textCharacters) {
        character->drawDebug(renderTarget, indentAddition, hue + hueOffset, hueOffset);
    }

    background->drawDebug(renderTarget, indent, indentAddition, hue + hueOffset, hueOffset);
}