#pragma once

#include "../../../../../interaction/interactionManager/interactionManager.hpp"
#include "../../../../../interaction/interactionStack/interactionStack.hpp"
#include "../line/baseLine.hpp"

using uint = unsigned;

namespace ui {
	class BaseTextBlock;
	
	class BaseCharacter {
	public:
		enum class Special {
			space,
			enter,
			no,
			fullLine,
		};
	
	protected:
		sf::Vector2f position;
		bool selection;
		bool active;
		
		bool rerender;
	
	public:
		BaseCharacter();
		
		virtual bool getRerender() const;
		
		virtual void setRerender(bool rerender);
		
		virtual void setActive(bool active);
		
		virtual sf::Vector2i getSizeTexture() = 0;
		
		virtual void init(sf::RenderTarget& renderTarget);
		
		virtual bool in(sf::Vector2f mousePosition);
		
		virtual void setSelection(bool selection);
		
		virtual void setPosition(sf::Vector2f position);
		
		virtual void resize(sf::Vector2f position, float endRender);
		
		virtual void move(sf::Vector2f position);
		
		virtual std::vector<BaseLine*>& getLine() = 0;
		
		virtual sf::Vector2f getPosition() const;
		
		virtual float getHeight() const = 0;
		
		virtual float getAdvance() = 0;
		
		virtual float getKerning(char32_t character) = 0;
		
		virtual bool isEnter();
		
		virtual Special isSpecial() = 0;
		
		virtual void draw(bool selection) = 0;
		
		virtual char32_t getChar() = 0;
		
		virtual float getMinAdvance();
		
		virtual void drawDebug(sf::RenderTarget& renderTarget, int indentAddition, uint hue, uint hueOffset) = 0;
		
		virtual ~BaseCharacter() = default;
	};
}