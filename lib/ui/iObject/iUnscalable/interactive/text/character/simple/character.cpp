#include "character.h"
#include "../../../../../iObject.hpp"

ui::Character::Character(char32_t character, TextVariables &textVariables, std::vector<BaseLine *>& lines)
        : character(character), textVariables(textVariables), vertexArray(sf::Quads, 4), lines(lines), selectionVertexArray(sf::Quads, 4){
    if(isSpecial() != BaseCharacter::Special::enter){
        glyph = textVariables.font->getGlyph(character, textVariables.size, textVariables.style & sf::Text::Style::Bold);

        texture = textVariables.font->getTexture(textVariables.size);

        vertexArray[0].texCoords = sf::Vector2f(sf::Vector2i{glyph.textureRect.left, glyph.textureRect.top});
        vertexArray[1].texCoords = sf::Vector2f(sf::Vector2i{glyph.textureRect.left + glyph.textureRect.width, glyph.textureRect.top});
        vertexArray[2].texCoords = sf::Vector2f(sf::Vector2i{glyph.textureRect.left + glyph.textureRect.width, glyph.textureRect.top + glyph.textureRect.height});
        vertexArray[3].texCoords = sf::Vector2f(sf::Vector2i{glyph.textureRect.left, glyph.textureRect.top + glyph.textureRect.height});

        vertexArray[0].color = textVariables.TextColor;
        vertexArray[1].color = textVariables.TextColor;
        vertexArray[2].color = textVariables.TextColor;
        vertexArray[3].color = textVariables.TextColor;

        vertexArray[0].position = {0, 0};
        vertexArray[1].position = sf::Vector2f{sf::Vector2i{glyph.textureRect.width, 0}};
        vertexArray[2].position = sf::Vector2f{sf::Vector2i{glyph.textureRect.width, glyph.textureRect.height}};
        vertexArray[3].position = sf::Vector2f{sf::Vector2i{0, glyph.textureRect.height}};

        selectionVertexArray[0].position = {0,            0};
        selectionVertexArray[1].position = {getAdvance(), 0};
        selectionVertexArray[2].position = {getAdvance(), getHeight()};
        selectionVertexArray[3].position = {0,            getHeight()};

        selectionVertexArray[0].color = textVariables.backgroundSelectionColor;
        selectionVertexArray[1].color = textVariables.backgroundSelectionColor;
        selectionVertexArray[2].color = textVariables.backgroundSelectionColor;
        selectionVertexArray[3].color = textVariables.backgroundSelectionColor;

        if (textVariables.style & sf::Text::Style::Italic){
            float italicShear = -0.26794;
            vertexArray[0].position.x += (vertexArray[0].position.y + glyph.bounds.top) * italicShear;
            vertexArray[1].position.x += (vertexArray[1].position.y + glyph.bounds.top) * italicShear;
            vertexArray[2].position.x += (vertexArray[2].position.y + glyph.bounds.top) * italicShear;
            vertexArray[3].position.x += (vertexArray[3].position.y + glyph.bounds.top) * italicShear;
        }

        vertexArray[0].position.y += glyph.bounds.top;
        vertexArray[1].position.y += glyph.bounds.top;
        vertexArray[2].position.y += glyph.bounds.top;
        vertexArray[3].position.y += glyph.bounds.top;

        selectionVertexArray[0].position.y -= getHeight();
        selectionVertexArray[1].position.y -= getHeight();
        selectionVertexArray[2].position.y -= getHeight();
        selectionVertexArray[3].position.y -= getHeight();
    }
}

void ui::Character::init(sf::RenderTarget &renderTarget) {
    this->renderTarget = &renderTarget;
}

void ui::Character::setActive(bool active) {
    BaseCharacter::setActive(active);
    if (active){
        for (int i = 0; i < 4; ++i) {
            vertexArray[i].color = textVariables.textSelectionColor;
            selectionVertexArray[i].color = textVariables.backgroundSelectionColor;
        }
    } else{
        for (int i = 0; i < 4; ++i) {
            vertexArray[i].color = textVariables.inactiveTextSelectionColor;
            selectionVertexArray[i].color = textVariables.inactiveBackgroundSelectionColor;
        }
    }
}

sf::Vector2i ui::Character::getSizeTexture() {
    if (getChar() == U' ')
        return {static_cast<int>(getAdvance()), static_cast<int>(getHeight())};
    return {glyph.textureRect.width, glyph.textureRect.height};
}

void ui::Character::setSelection(bool selection) {
    BaseCharacter::setSelection(selection);
    if (selection){
        vertexArray[0].color = textVariables.textSelectionColor;
        vertexArray[1].color = textVariables.textSelectionColor;
        vertexArray[2].color = textVariables.textSelectionColor;
        vertexArray[3].color = textVariables.textSelectionColor;
    } else{
        vertexArray[0].color = textVariables.TextColor;
        vertexArray[1].color = textVariables.TextColor;
        vertexArray[2].color = textVariables.TextColor;
        vertexArray[3].color = textVariables.TextColor;
    }
}

void ui::Character::draw() {
    if(isSpecial() != BaseCharacter::Special::enter){
        if (selection)
            renderTarget->draw(selectionVertexArray);
        renderTarget->draw(vertexArray, &texture);
    }
}

ui::BaseCharacter::Special ui::Character::isSpecial() {
    if (character == L' ')
        return BaseCharacter::Special::space;
    else if (character == L'\n')
        return BaseCharacter::Special::enter;
    return BaseCharacter::Special::no;
}

char32_t ui::Character::getChar() {
    return character;
}

float ui::Character::getKerning(char32_t character) {
    return textVariables.font->getKerning(this->character, character, textVariables.size);
}

float ui::Character::getAdvance() {
    return glyph.advance;
}

float ui::Character::getHeight() {
    return textVariables.size;
}

void ui::Character::setPosition(const sf::Vector2f position) {
    move(position - this->position);
    BaseCharacter::setPosition(position);
}

void ui::Character::move(sf::Vector2f position) {
    BaseCharacter::move(position);
    vertexArray[0].position += position;
    vertexArray[1].position += position;
    vertexArray[2].position += position;
    vertexArray[3].position += position;

    selectionVertexArray[0].position += position;
    selectionVertexArray[1].position += position;
    selectionVertexArray[2].position += position;
    selectionVertexArray[3].position += position;
}

std::vector<ui::BaseLine *> & ui::Character::getLine() {
    return lines;
}

bool ui::Character::in(sf::Vector2f mousePosition) {

    return  position.x < mousePosition.x && position.x + getAdvance() > mousePosition.x &&
            position.y - getHeight() < mousePosition.y && position.y > mousePosition.y;
}

bool ui::Character::debug = false;

void ui::Character::setDebug(bool debug) {
    ui::Character::debug = debug;
}

void ui::Character::drawDebug(sf::RenderTarget &renderTarget, int indentAddition, uint hue, uint hueOffset) {
    if (debug){
        sf::Vector2f size{getAdvance() - 2.0f, getHeight() - 2.0f};
        sf::Vector2f position{this->getPosition() + sf::Vector2f{1.0f, 1.0f - getHeight()}};
        if (size.x > 0 && size.y > 0){
			sf::Color color{ui::IObject::HSVtoRGB(static_cast<float>(hue % 360))};
			
			sf::RectangleShape rectangle{size};
			rectangle.setPosition(position);
			rectangle.setFillColor(sf::Color::Transparent);
			rectangle.setOutlineThickness(1);
			rectangle.setOutlineColor(color);
			
			renderTarget.draw(rectangle);
        }
    }
}