#pragma once

#include "../simple/textBlock.h"
#include "../../../../../../interaction/iInteraction/iInteraction.h"

namespace ui {
    class InteractiveTextBlock : public TextBlock {
    private:
        bool interact;
        bool oldInteract;

    protected:
        int indexInteraction;
        IInteraction* interaction;
    public:
        InteractiveTextBlock(IInteraction* interaction, std::wstring text, sf::Color color, sf::Font &font, sf::Text::Style style = {}, int size = 0);
        InteractiveTextBlock(IInteraction* interaction, std::wstring text, sf::Color color, sf::Text::Style style = {}, int size = 0);
        InteractiveTextBlock(int indexInteraction, std::wstring text, sf::Color color, sf::Font &font, sf::Text::Style style = {}, int size = 0);
        InteractiveTextBlock(int indexInteraction, std::wstring text, sf::Color color, sf::Text::Style style = {}, int size = 0);

        void init(ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack);

        void update() override;
        bool updateInteractions(sf::Vector2f mousePosition) override;
    };
}