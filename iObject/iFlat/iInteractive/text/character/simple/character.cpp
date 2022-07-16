#include <cmath>
#include "character.h"
#include "../../../../../iObject.h"

ui::Character::Character(wchar_t character, TextVariables &textVariables)
        : character(character), textVariables(textVariables){
    if(isSpecial() != BaseCharacter::Special::enter){
        glyph = textVariables.font->getGlyph(character, textVariables.size, textVariables.style);
        sprite.setTexture(textVariables.font->getTexture(textVariables.size));
        sprite.setTextureRect(glyph.textureRect);
        sprite.setOrigin(-glyph.bounds.left, -glyph.bounds.top);
        sprite.setColor(textVariables.TextColor);
    }
}

void ui::Character::init(sf::RenderTarget &renderTarget) {
    this->renderTarget = &renderTarget;
}

void ui::Character::draw() {
    if(isSpecial() != BaseCharacter::Special::enter){
        renderTarget->draw(sprite);
    }
}

ui::BaseCharacter::Special ui::Character::isSpecial() {
    if (character == L' ')
        return BaseCharacter::Special::space;
    else if (character == L'\n')
        return BaseCharacter::Special::enter;
    return BaseCharacter::Special::no;
}

wchar_t ui::Character::getChar() {
    return character;
}

float ui::Character::getKerning(wchar_t character) {
    return textVariables.font->getKerning(this->character, character, textVariables.size);
}

float ui::Character::getAdvance() {
    return glyph.advance;
}

float ui::Character::getHeight() {
    return textVariables.size;
}

void ui::Character::move(sf::Vector2f position) {
    BaseCharacter::move(position);
    sprite.setPosition(this->position);
}

void ui::Character::setPosition(const sf::Vector2f position) {
    BaseCharacter::setPosition(position);
    sprite.setPosition(position);
}

bool ui::Character::in(sf::Vector2f mousePosition) {

    return  position.x < mousePosition.x && position.x + getAdvance() > mousePosition.x &&
            position.y - getHeight() < mousePosition.y && position.y > mousePosition.y;
}

void ui::Character::drawDebug(sf::RenderTarget &renderTarget, int indentAddition, uint hue, uint hueOffset) {
    sf::Vector2f size{getAdvance(), getHeight()};
    size = {size.x - 1.0f, size.y - 1.0f};
    sf::Vector2f position{this->getPosition() - sf::Vector2f{0.f, getHeight()}};
    position = {position.x + 1.0f, position.y};
    if (size.x > 0 && size.y > 0){
        sf::Color color{ui::IObject::HSVtoRGB(static_cast<float>(hue % 360))};
        sf::Vertex frame[] {
            {position, color},
            {{position.x + size.x, position.y}, color},
            {position + size, color},
            {{position.x, position.y + size.y}, color},
            {position, color},
        };

        renderTarget.draw(frame, 5, sf::LinesStrip);
    }
}
