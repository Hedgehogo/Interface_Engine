#include "baseTextBlock.h"

ui::BaseTextBlock::BaseTextBlock() {}

void ui::BaseTextBlock::init(ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack) {
    this->interactionManager = &interactionManager;
    this->interactionStack = &interactionStack;
}

void ui::BaseTextBlock::setTextVariables(sf::Color TextColor, sf::Color textSelectionColor, sf::Color backgroundSelectionColor, sf::Font *font , uint size) {
    if (textVariables.TextColor == sf::Color(255, 255, 255, 0))
        textVariables.TextColor = TextColor;
    if (textVariables.textSelectionColor == sf::Color(255, 255, 255, 0))
        textVariables.textSelectionColor = textSelectionColor;
    if (textVariables.backgroundSelectionColor == sf::Color(255, 255, 255, 0))
        textVariables.backgroundSelectionColor = backgroundSelectionColor;
    if (textVariables.font == nullptr)
        textVariables.font = font;
    if (textVariables.size == 0)
        textVariables.size = size;
}
