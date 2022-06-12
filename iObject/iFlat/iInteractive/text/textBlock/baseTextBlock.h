#pragma once
#include "SFML/Graphics.hpp"
#include "../../simple/interactiveSimple.h"
#include "../indivisible/baseIndivisible.h"
#include "../../../../../interaction/interactionStack/interactionStack.h"
namespace ui {
	class BaseTextBlock{
	protected:
        ui::InteractionManager *interactionManager;
        ui::InteractionStack *interactionStack;
		sf::Text text;

        uint lineSpacing;
	public:
        struct Edge{
            int start, end;
        };
        BaseTextBlock(std::wstring text, sf::Color color, sf::Text::Style style, sf::Font &font, int size = 0);
        BaseTextBlock(std::wstring text, sf::Color color, sf::Text::Style style, int size = 0);

        void setTextVariables(uint lineSpacing, int size, sf::Font *font);
        virtual void init(ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack);

        virtual std::vector<BaseIndivisible*> divide() = 0;

        virtual void update() = 0;

        virtual bool updateInteractions(sf::Vector2f mousePosition) = 0;
    };
}
