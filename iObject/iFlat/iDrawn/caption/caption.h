#pragma once
#include "../iDrawn.h"

namespace ui {
	class Caption : public IDrawn {
	protected:
		static sf::Color defaultColor;
		static int defaultSize;
		
		sf::Text text;
		std::wstring str;
		IDrawn* background;
		sf::Vector2f minimumSize;
		
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
	
	public:
		static void setDefaultColor(sf::Color color = sf::Color::White);
		
		static void setDefaultSize(int size);
		
		Caption(const std::wstring& text, IDrawn *background, sf::Font &font, sf::Vector2f minimumSize, int size = defaultSize, sf::Color color = defaultColor, sf::Text::Style style = {}, float rotation = 0);
		
		Caption(const std::wstring& text, IDrawn *background, sf::Font &font, int size = defaultSize, sf::Color color = defaultColor, sf::Text::Style style = {}, float rotation = 0);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getPosition() override;
		
		sf::Vector2f getAreaSize() override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
	protected:
		Caption(sf::Text text, IDrawn* background, std::wstring str, sf::Vector2f minimumSize);
		
	public:
		Caption* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition) override;
	};
}
