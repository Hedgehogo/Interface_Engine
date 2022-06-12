#include "baseIndivisible.h"
#include "../textBlock/baseTextBlock.h"

ui::BaseIndivisible::BaseIndivisible(ui::BaseTextBlock *parent) : parent(parent) {}

void ui::BaseIndivisible::init(sf::RenderWindow &window) {
    this->window = &window;
}

const sf::Vector2f &ui::BaseIndivisible::getSize() const {
    return size;
}

void ui::BaseIndivisible::setPosition(const sf::Vector2f &position) {
    BaseIndivisible::position = position;
}
