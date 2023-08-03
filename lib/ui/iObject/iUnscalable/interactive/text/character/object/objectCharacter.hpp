#pragma once

#include "../baseCharacter.hpp"
#include "../../../../iScalable/iScalable.hpp"

namespace ui {
	class ObjectCharacter : public BaseCharacter {
	public:
		ObjectCharacter(IScalable* object, bool fullLine = false);
		
		void setPosition(sf::Vector2f position) override;
		
		void resize(sf::Vector2f position, float endPosition) override;
		
		void move(sf::Vector2f position) override;
		
		std::vector<BaseLine*>& getLine();
		
		sf::Vector2f getPosition() const override;
		
		sf::Vector2i getSizeTexture() override;
		
		float getHeight() const override;
		
		float getAdvance() override;
		
		float getKerning(char32_t) override;
		
		Special isSpecial() override;
		
		void draw(bool) override;
		
		char32_t getChar() override;
		
		float getMinAdvance() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indentAddition, uint hue, uint hueOffset) override;
		
		~ObjectCharacter() override;
	
	protected:
		IScalable* object;
		std::vector<BaseLine*> lines;
		BaseCharacter::Special special;
	};
}