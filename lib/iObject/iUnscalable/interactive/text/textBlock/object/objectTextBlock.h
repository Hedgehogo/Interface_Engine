#pragma once
#include "../baseTextBlock.h"
#include "SFML/Graphics.hpp"
#include "../../character/object/objectCharacter.h"
namespace ui{
    class ObjectTextBlock  : public BaseTextBlock {
        std::vector<BaseLine *> lines;
        sf::Vector2f size;
        ObjectCharacter* objectCharacter;
        bool isCharacter;
        IObject* object;
    public:
        ObjectTextBlock(ui::IObject* object, sf::Vector2f size = {0, 0}, bool isCharacter = true);

        void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;

        bool in(sf::Vector2f mousePosition) override;

        std::vector<BaseCharacter*> getCharacters() override;

        void update() override;

        bool updateInteractions(sf::Vector2f mousePosition) override;

        BaseTextBlock *copy() override;
    };
}