#pragma once
#include "../baseTextBlock.hpp"
#include "../../character/object/objectCharacter.hpp"
namespace ui{
    class ObjectTextBlock  : public BaseTextBlock {
        std::vector<BaseLine *> lines;
        sf::Vector2f size;
        ObjectCharacter* objectCharacter;
        bool isCharacter;
        IScalable* object;
    public:
        ObjectTextBlock(IScalable* object, sf::Vector2f size = {0, 0}, bool isCharacter = true);

        void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) override;

        bool in(sf::Vector2f mousePosition) override;

        std::vector<BaseCharacter*> getCharacters() override;

        void update() override;

        bool updateInteractions(sf::Vector2f mousePosition) override;

        BaseTextBlock *copy() override;
    };
	
	bool convertPointer(const YAML::Node &node, ObjectTextBlock *&objectTextBlock);
}