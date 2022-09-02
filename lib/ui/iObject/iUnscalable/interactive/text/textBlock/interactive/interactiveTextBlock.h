#pragma once

#include "../simple/textBlock.h"
#include "../../../../../../interaction/iInteraction/iInteraction.hpp"

namespace ui {
    class InteractiveTextBlock : public TextBlock {
    protected:
        InteractionManager* interactionManager;

        bool interact;
        bool oldInteract;

        int indexInteraction;
        IInteraction* interaction;
    public:
        InteractiveTextBlock(IInteraction* interaction, std::u32string  text, sf::Color textColor = sf::Color(255, 255, 255, 0),
                             sf::Font *font = nullptr, sf::Text::Style style = {}, std::vector<BaseLine*> lines = {}, int size = 0,
                             sf::Color textSelectionColor = sf::Color(255, 255, 255, 0),
                             sf::Color backgroundSelectionColor = sf::Color(255, 255, 255, 0));
        InteractiveTextBlock(int indexInteraction, std::u32string  text, sf::Color textColor = sf::Color(255, 255, 255, 0),
                             sf::Font *font = nullptr, sf::Text::Style style = {}, std::vector<BaseLine*> lines = {}, int size = 0,
                             sf::Color textSelectionColor = sf::Color(255, 255, 255, 0),
                             sf::Color backgroundSelectionColor = sf::Color(255, 255, 255, 0));

        ~InteractiveTextBlock();

        void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager);

        std::vector<BaseCharacter*> getCharacters() override;

        bool in(sf::Vector2f mousePosition);

        void update() override;
        bool updateInteractions(sf::Vector2f mousePosition) override;

    protected:
        InteractiveTextBlock(std::u32string  str, TextVariables textVariables, ui::IInteraction *interaction);
        InteractiveTextBlock(std::u32string  str, TextVariables textVariables, int indexInteraction);
    public:

        InteractiveTextBlock * copy() override;

        static InteractiveTextBlock* createFromYaml(const YAML::Node &node);
    };
}