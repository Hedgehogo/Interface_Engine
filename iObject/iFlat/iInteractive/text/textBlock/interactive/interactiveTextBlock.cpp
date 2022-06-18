#include "interactiveTextBlock.h"

ui::InteractiveTextBlock::InteractiveTextBlock(ui::IInteraction *interaction, std::wstring text, sf::Color textColor, sf::Font *font, sf::Text::Style style, int size, sf::Color textSelectionColor,
                                               sf::Color backgroundSelectionColor) :
    interaction(interaction), TextBlock(text, textColor, font, style, size, textSelectionColor, backgroundSelectionColor), interact(false), oldInteract(false) {}

ui::InteractiveTextBlock::InteractiveTextBlock(int indexInteraction, std::wstring text, sf::Color textColor, sf::Font *font, sf::Text::Style style, int size, sf::Color textSelectionColor,
                                               sf::Color backgroundSelectionColor) :
    indexInteraction(indexInteraction), TextBlock(text, textColor, font, style, size, textSelectionColor, backgroundSelectionColor), interact(false), oldInteract(false) {}

void ui::InteractiveTextBlock::init(ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack) {
    this->interactionManager = &interactionManager;
    this->interactionStack = &interactionStack;

    interaction = interactionStack.at(indexInteraction);
}

void ui::InteractiveTextBlock::update() {
    if(interact != oldInteract) {
        oldInteract = interact;
        if(interact) {
            interactionManager->addInteraction(*interaction);
        } else {
            interactionManager->deleteInteraction(*interaction);
        }
    }
    interact = false;
}

bool ui::InteractiveTextBlock::updateInteractions(sf::Vector2f mousePosition) {
    interact = true;
    return true;
}

std::vector<ui::BaseCharacter *> ui::InteractiveTextBlock::character() {
    for (wchar_t character : str) {
        textCharacters.push_back(new ui::Character(character, textVariables, this, interaction));
    }
    return textCharacters;
}

bool ui::InteractiveTextBlock::in(sf::Vector2f mousePosition) {
    for (ui::BaseCharacter *character : textCharacters) {
        if (character->in(mousePosition)){
            return true;
        }
    }
    return false;
}
