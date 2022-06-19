#pragma once
#include "../iDrawn.h"

namespace ui {
	class Caption : public IDrawn {
	protected:
		static sf::Color defaultColor;
		static int defaultSize;
		
		std::wstring str;
		sf::Text text;
		IDrawn* background;
		sf::Vector2f minimumSize;
		
		void init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelManager &overlayStack) override;
	
	public:
		static void setDefaultColor(sf::Color color = sf::Color::White);
		
		static void setDefaultSize(int size);
		
		Caption(const std::wstring& text, IDrawn *background, sf::Font &font, sf::Vector2f minimumSize, int size = defaultSize, sf::Color color = defaultColor, sf::Text::Style style = {}, float rotation = 0);
		
		Caption(const std::wstring& text, IDrawn *background, sf::Font &font, int size = defaultSize, sf::Color color = defaultColor, sf::Text::Style style = {}, float rotation = 0);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
	};
}
