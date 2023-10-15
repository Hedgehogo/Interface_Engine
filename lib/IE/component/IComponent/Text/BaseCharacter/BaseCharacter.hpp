#pragma once

#include "IE/interaction/InteractionManager/InteractionManager.hpp"
#include "IE/interaction/InteractionStack/InteractionStack.hpp"
#include "../BaseLine/BaseLine.hpp"

using uint = unsigned;

namespace ie {
	class BaseTextBlock;
	
	class BaseCharacter {
	public:
		enum class Special {
			Space,
			Enter,
			No,
			FullLine,
		};
	
		BaseCharacter();
		
		virtual bool getRerender() const;
		
		virtual void setRerender(bool rerender);
		
		virtual void setActive(bool active);
		
		virtual sf::Vector2i getSizeTexture() = 0;
		
		virtual bool in(sf::Vector2f mousePosition);
		
		virtual void setSelection(bool selection);
		
		virtual void setPosition(sf::Vector2f position);
		
		virtual void setKerning(float kerning);
		
		virtual void resize(sf::Vector2f position, float);
		
		virtual void move(sf::Vector2f position);
		
		virtual const std::vector<BoxPtr<BaseLine>>& getLine() = 0;
		
		virtual sf::Vector2f getPosition() const;
		
		virtual float getHeight() const = 0;
		
		virtual float getAdvance() = 0;
		
		virtual float getKerning(char32_t) = 0;
		
		virtual bool isEnter();
		
		virtual Special isSpecial() = 0;
		
		virtual void draw(bool selection) = 0;
		
		virtual char32_t getChar() = 0;
		
		virtual float getMinAdvance();
		
		virtual void drawDebug(sf::RenderTarget& renderTarget, int indentAddition, uint hue, uint hueOffset) = 0;
		
		virtual ~BaseCharacter() = default;
	
	protected:
		sf::Vector2f position;
		bool selection;
		bool active;
		bool rerender;
	};
}