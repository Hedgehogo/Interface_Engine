#pragma once

#include "../BaseCharacter.hpp"
#include "../../../IScalable/IScalable.hpp"

namespace ie {
	class ObjectCharacter : public BaseCharacter {
	public:
		explicit ObjectCharacter(BoxPtr<IScalable>&& object, bool fullLine = false);
		
		void setPosition(sf::Vector2f position) override;
		
		void resize(sf::Vector2f position, float endPosition) override;
		
		void move(sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition);
		
		const std::vector<BoxPtr<BaseLine>>& getLine() override;
		
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
	
	protected:
		BoxPtr<IScalable> object;
		std::vector<BoxPtr<BaseLine>> lines;
		BaseCharacter::Special special;
	};
}