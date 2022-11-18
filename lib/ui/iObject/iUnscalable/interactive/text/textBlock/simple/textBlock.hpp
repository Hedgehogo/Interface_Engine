#pragma once
#include "../baseTextBlock.hpp"
#include "../../character/simple/character.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/determine/determine.hpp"

namespace ui {
	class TextBlock : public BaseTextBlock {
    protected:
        std::u32string  str;

        std::vector<BaseCharacter*> textCharacters;
        std::vector<BaseLine*> lines;

	public:
        TextBlock(std::u32string  str, TextVariables textVariables, std::vector<BaseLine*> lines);

        TextBlock(std::u32string text, sf::Color textColor = nullColor, sf::Font *font = nullptr, sf::Text::Style style = {}, std::vector<BaseLine *> lines = {}, int size = 0, sf::Color textSelectionColor = nullColor,
                  sf::Color backgroundSelectionColor = nullColor, sf::Color inactiveTextSelectionColor = nullColor, sf::Color inactiveBackgroundSelectionColor = nullColor);
        std::vector<BaseCharacter*> getCharacters() override;

        bool in(sf::Vector2f mousePosition);

        void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) override;

        void update() override;

        bool updateInteractions(sf::Vector2f mousePosition) override;

        TextBlock * copy() override;

        ~TextBlock() override;
	};
	
	bool convertPointer(const YAML::Node &node, TextBlock *&textBlock);

	template<>
	bool determine<TextBlock>(const YAML::Node &node);
}