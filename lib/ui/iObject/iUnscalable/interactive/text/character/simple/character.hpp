#pragma once

#include <string>
#include "../baseCharacter.hpp"
#include "../../variables/textVariables.hpp"

namespace ui {
	class Character : public BaseCharacter {
	public:
		Character(char32_t character, TextVariables& textVariables, std::vector<BaseLine*>& lines);
		
		void init(sf::RenderTarget& renderTarget) override;
		
		void setActive(bool active) override;
		
		sf::Vector2i getSizeTexture() override;
		
		void setSelection(bool selection) override;
		
		void draw(bool selection) override;
		
		void move(sf::Vector2f position) override;
		
		std::vector<BaseLine*>& getLine();
		
		bool in(sf::Vector2f mousePosition) override;
		
		float getHeight() const override;
		
		float getAdvance() override;
		
		float getKerning(char32_t character) override;
		
		Special isSpecial() override;
		
		char32_t getChar() override;
		
		void setPosition(const sf::Vector2f position) override;
	
		static void setDebug(bool debug);
		
		void drawDebug(sf::RenderTarget& renderTarget, int indentAddition, uint hue, uint hueOffset) override;
	
	private:
		static bool debug;
	
	protected:
		sf::RenderTarget* renderTarget;
		
		char32_t character;
		
		sf::Glyph glyph;
		TextVariables& textVariables;
		sf::VertexArray vertexArray;
		sf::VertexArray selectionVertexArray;
		sf::Texture texture;
		sf::Vector2f origin;
		
		std::vector<BaseLine*>& lines;
	};
}