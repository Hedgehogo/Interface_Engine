#include "character.h"

ui::Character::Character(wchar_t character, TextVariables &textVariables)
        : character(character), textVariables(textVariables){
    glyph = textVariables.font->getGlyph(character, textVariables.size, textVariables.style);
    sprite.setTexture(textVariables.font->getTexture(textVariables.size));
    sprite.setTextureRect(glyph.textureRect);
    sprite.setOrigin(-glyph.bounds.left, -glyph.bounds.top);
    sprite.setColor(textVariables.TextColor);
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

void ui::Character::init(sf::RenderTarget &renderTarget) {
    this->renderTarget = &renderTarget;
}
