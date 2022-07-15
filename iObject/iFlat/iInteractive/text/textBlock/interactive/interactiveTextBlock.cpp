#include "interactiveTextBlock.h"

ui::InteractiveTextBlock::InteractiveTextBlock(ui::IInteraction *interaction, std::wstring text, sf::Color textColor, sf::Font *font, sf::Text::Style style, int size, sf::Color textSelectionColor,
                                               sf::Color backgroundSelectionColor) :
    interaction(interaction), TextBlock(text, textColor, font, style, size, textSelectionColor, backgroundSelectionColor), interact(false), oldInteract(false), indexInteraction(-1) {}

ui::InteractiveTextBlock::InteractiveTextBlock(int indexInteraction, std::wstring text, sf::Color textColor, sf::Font *font, sf::Text::Style style, int size, sf::Color textSelectionColor,
                                               sf::Color backgroundSelectionColor) :
    indexInteraction(indexInteraction), TextBlock(text, textColor, font, style, size, textSelectionColor, backgroundSelectionColor), interact(false), oldInteract(false) {}

void ui::InteractiveTextBlock::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
    BaseTextBlock::init(renderTarget, interactionStack, interactionManager, panelManager);
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
        textCharacters.push_back(new ui::Character(character, textVariables));
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

ui::InteractiveTextBlock::InteractiveTextBlock(std::wstring str, TextVariables textVariables, ui::IInteraction *interaction) :
    TextBlock(str, textVariables), interaction(interaction), interact(false), oldInteract(false) {}

ui::InteractiveTextBlock::InteractiveTextBlock(std::wstring str, TextVariables textVariables, int indexInteraction) :
    TextBlock(str, textVariables), indexInteraction(indexInteraction), interact(false), oldInteract(false) {}

ui::InteractiveTextBlock *ui::InteractiveTextBlock::copy() {
    if (indexInteraction == -1)
        return new InteractiveTextBlock(str, textVariables, interaction->copy());
    else
        return new InteractiveTextBlock(str, textVariables, indexInteraction);
}

