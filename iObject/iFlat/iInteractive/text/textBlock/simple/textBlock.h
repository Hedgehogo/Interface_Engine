#pragma once
#include "../baseTextBlock.h"

#include "../../character/simple/character.h"

namespace ui {
	class TextBlock : public BaseTextBlock {
    protected:
        std::wstring str;
        std::vector<BaseCharacter*> textCharacters;

	public:
        TextBlock(std::wstring str, TextVariables textVariables);

        TextBlock(std::wstring text, sf::Color textColor = sf::Color(255, 255, 255, 0),
                  sf::Font *font = nullptr, sf::Text::Style style = {}, int size = 0,
                  sf::Color textSelectionColor = sf::Color(255, 255, 255, 0),
                  sf::Color backgroundSelectionColor = sf::Color(255, 255, 255, 0));
        std::vector<BaseCharacter*> getCharacters() override;

        bool in(sf::Vector2f mousePosition);

        void init(sf::RenderTarget &renderTarget, ui::InteractionStack &interactionStack, ui::InteractionManager &interactionManager, ui::PanelManager &panelManager) override;

        void update() override;
        bool updateInteractions(sf::Vector2f mousePosition) override;
        TextBlock * copy() override;
	};
}