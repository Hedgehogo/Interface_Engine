#include "interactiveTextBlock.h"

ui::InteractiveTextBlock::InteractiveTextBlock(IInteraction* interaction, std::wstring text, sf::Color color, sf::Font &font, sf::Text::Style style, int size) :
    interaction(interaction), TextBlock(text, color, font, style, size), interact(false), oldInteract(false) {}

ui::InteractiveTextBlock::InteractiveTextBlock(IInteraction* interaction, std::wstring text, sf::Color color, sf::Text::Style style, int size) :
        interaction(interaction), TextBlock(text, color, style, size), interact(false), oldInteract(false) {}

ui::InteractiveTextBlock::InteractiveTextBlock(int indexInteraction, std::wstring text, sf::Color color, sf::Font &font, sf::Text::Style style, int size) :
    indexInteraction(indexInteraction), TextBlock(text, color, style, size), interact(false), oldInteract(false) {}

ui::InteractiveTextBlock::InteractiveTextBlock(int indexInteraction, std::wstring text, sf::Color color, sf::Text::Style style, int size) :
        indexInteraction(indexInteraction), TextBlock(text, color, style, size), interact(false), oldInteract(false) {}

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
