#include "baseCharacter.h"
#include "../textBlock/baseTextBlock.h"

ui::BaseCharacter::BaseCharacter() {}

void ui::BaseCharacter::init(sf::RenderTarget &renderTarget) {}

void ui::BaseCharacter::setPosition(sf::Vector2f position) {
    this->position = position;
}

bool ui::BaseCharacter::in(sf::Vector2f mousePosition) {
    return position.x < mousePosition.x && position.x + getAdvance() > mousePosition.x &&
           position.y < mousePosition.y && position.y + getHeight()> mousePosition.y;
}

const sf::Vector2f &ui::BaseCharacter::getPosition() const {
    return position;
}

void ui::BaseCharacter::move(sf::Vector2f position) {
    this->position += position;
}

bool ui::BaseCharacter::isEnter() {
    return isSpecial() == Special::enter;
}

