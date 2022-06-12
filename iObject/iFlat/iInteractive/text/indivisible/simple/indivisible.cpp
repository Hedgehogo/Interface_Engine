#include "indivisible.h"
#include <iostream>

ui::Indivisible::Indivisible(sf::Text text, ui::BaseTextBlock *parent) : BaseIndivisible(parent), text(text){
    size.y = text.getGlobalBounds().height;
    size.x = text.getGlobalBounds().width;
}

void ui::Indivisible::draw() {
    text.setPosition(position);
    window->draw(text);
}

ui::BaseIndivisible::special ui::Indivisible::isSpecial() {
    sf::String str = text.getString();
    if (str == L" ")
        return BaseIndivisible::special::spase;
    else if (str == L"\n")
        return BaseIndivisible::special::enter;
    return BaseIndivisible::special::no;
}