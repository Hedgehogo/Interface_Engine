#pragma once

#include <string>
#include "../BaseCharacter.hpp"
#include "../../TextVariables/TextVariables.hpp"

namespace ie {
	class Character : public BaseCharacter {
	public:
		Character(char32_t character, TextVariables& textVariables, std::vector<BoxPtr<BaseLine>>& lines, orl::Option<sf::RenderTarget&> renderTarget);
		
		void setActive(bool active) override;
		
		sf::Vector2i getSizeTexture() override;
		
		void setSelection(bool selection) override;
		
		void draw(bool selection) override;
		
		void setKerning(float kerning) override;
		
		void move(sf::Vector2f position) override;
		
		const std::vector<BoxPtr<BaseLine>>& getLine();
		
		bool in(sf::Vector2f mousePosition) override;
		
		float getHeight() const override;
		
		float getAdvance() override;
		
		float getKerning(char32_t character) override;
		
		Special isSpecial() override;
		
		char32_t getChar() override;
		
		void setPosition(sf::Vector2f position) override;
	
		static void setDebug(bool debug);
		
		void drawDebug(sf::RenderTarget& renderTarget, int, uint hue, uint) override;
	
	private:
		static bool debug;
	
	protected:
		orl::Option<sf::RenderTarget&> renderTarget;
		
		char32_t character;
		
		sf::Glyph glyph;
		float advance;
		float kerning;
		TextVariables& textVariables;
		sf::VertexArray vertexArray;
		sf::VertexArray selectionVertexArray;
		sf::Texture texture;
		sf::Vector2f origin;
		
		std::vector<BoxPtr<BaseLine>>& lines;
	};
}