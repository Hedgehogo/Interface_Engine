#pragma once

#include "../simple/textBlock.h"
#include "../../../../../../interaction/iInteraction/iInteraction.h"

namespace ui {
    class InteractiveTextBlock : public TextBlock {
    protected:
        InteractionManager* interactionManager;

        bool interact;
        bool oldInteract;

        int indexInteraction;
        IInteraction* interaction;
    public:
        InteractiveTextBlock(IInteraction* interaction, std::wstring text, sf::Color textColor = sf::Color(255, 255, 255, 0),
                             sf::Font *font = nullptr, sf::Text::Style style = {}, int size = 0,
                             sf::Color textSelectionColor = sf::Color(255, 255, 255, 0),
                             sf::Color backgroundSelectionColor = sf::Color(255, 255, 255, 0));
        InteractiveTextBlock(int indexInteraction, std::wstring text, sf::Color textColor = sf::Color(255, 255, 255, 0),
                             sf::Font *font = nullptr, sf::Text::Style style = {}, int size = 0,
                             sf::Color textSelectionColor = sf::Color(255, 255, 255, 0),
                             sf::Color backgroundSelectionColor = sf::Color(255, 255, 255, 0));

        ~InteractiveTextBlock();

        void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager);

        std::vector<BaseCharacter*> getCharacters() override;

        bool in(sf::Vector2f mousePosition);

        void update() override;
        bool updateInteractions(sf::Vector2f mousePosition) override;

    protected:
        InteractiveTextBlock(std::wstring str, TextVariables textVariables, ui::IInteraction *interaction);
        InteractiveTextBlock(std::wstring str, TextVariables textVariables, int indexInteraction);
    public:

        InteractiveTextBlock * copy() override;
    };
}