#include "textBlock.h"


ui::TextBlock::TextBlock(std::wstring text, sf::Color textColor, sf::Font *font, sf::Text::Style style, int size, sf::Color textSelectionColor, sf::Color backgroundSelectionColor) :
    str(text){
    textVariables.TextColor = textColor;
    textVariables.font = font;
    textVariables.style = style;
    textVariables.size = size;
    textVariables.textSelectionColor = textSelectionColor;
    textVariables.backgroundSelectionColor = backgroundSelectionColor;
}

std::vector<ui::BaseCharacter*> ui::TextBlock::character() {
    std::vector<ui::BaseCharacter*> result;
    for (wchar_t character : str) {
        result.push_back(new ui::Character(character, textVariables, this, nullptr));
    }
    return result;
}

void ui::TextBlock::update() {}
bool ui::TextBlock::updateInteractions(sf::Vector2f mousePosition) {
    return false;
}

bool ui::TextBlock::in(sf::Vector2f mousePosition) {
    return false;
}