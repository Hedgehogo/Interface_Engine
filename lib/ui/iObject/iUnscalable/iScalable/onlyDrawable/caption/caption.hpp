#pragma once
#include "../onlyDrawable.hpp"
#include "../../../../../../yaml/yamlWithSfml/buffer/buffer.hpp"

namespace ui {
	class Caption : public OnlyDrawable {
	protected:
		static sf::Color defaultColor;
		static int defaultSize;
		
		sf::Text text;
		sf::String str;
		OnlyDrawable* background;
		sf::Vector2f minimumSize;
		DrawManager drawManager;
		
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;
	
	public:
		static void setDefaultColor(sf::Color color = sf::Color::White);
		
		static void setDefaultSize(int size);
		
		Caption(sf::String text, OnlyDrawable *background, sf::Font &font, sf::Vector2f minSize, int fontSize = defaultSize, sf::Color color = defaultColor, sf::Text::Style style = {}, float rotation = 0);
		
		Caption(sf::String text, OnlyDrawable *background, sf::Font &font, int fontSize = defaultSize, sf::Color color = defaultColor, sf::Text::Style style = {}, float rotation = 0);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getAreaPosition() override;
		
		sf::Vector2f getAreaSize() override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
	protected:
		Caption(sf::Text text, OnlyDrawable* background, sf::String str, sf::Vector2f minimumSize);
		
	public:
		Caption* copy() override;
		
		static Caption* createFromYaml(const YAML::Node &node);
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
