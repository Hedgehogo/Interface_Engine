#include "baseCharacter.h"
#include "../textBlock/baseTextBlock.h"

ui::BaseCharacter::BaseCharacter(BaseTextBlock *parent, IInteraction *interaction) : parent(parent) {}

void ui::BaseCharacter::init(sf::RenderWindow &window) {
    this->window = &window;
}

void ui::BaseCharacter::setPosition(const sf::Vector2f position) {
    BaseCharacter::position = position;
}

bool ui::BaseCharacter::in(sf::Vector2f mousePosition) {
    return position.x < mousePosition.x && position.x + getAdvance() > mousePosition.x &&
           position.y < mousePosition.y && position.y + getHeight()> mousePosition.y;
}