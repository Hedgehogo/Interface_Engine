#include "baseIndivisible.h"
#include "../textBlock/baseTextBlock.h"

ui::BaseIndivisible::BaseIndivisible(ui::BaseTextBlock *parent) : parent(parent) {}

void ui::BaseIndivisible::init(sf::RenderWindow &window, ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack) {
    this->window = &window;
    parent->init(interactionManager, interactionStack);
}

const sf::Vector2f &ui::BaseIndivisible::getSize() const {
    return size;
}

void ui::BaseIndivisible::setPosition(const sf::Vector2f &position) {
    BaseIndivisible::position = position;
}

bool ui::BaseIndivisible::in(sf::Vector2f mousePosition) {
    return position.x < mousePosition.x && position.x + size.x > mousePosition.x &&
           position.y < mousePosition.y && position.y + size.y > mousePosition.y;
}

void ui::BaseIndivisible::update() {
    parent->update();
}

bool ui::BaseIndivisible::updateInteractions(sf::Vector2f mousePosition) {
    return parent->updateInteractions(mousePosition);
}
