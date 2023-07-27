#pragma once

#include "../interactiveSimple.hpp"
#include "../../../uninteractive/uninteractive.hpp"

namespace ui {
	class BaseButton : public Interactive_Simple {
	protected:
		void copy(BaseButton* button);
	
	public:
		BaseButton(IScalable* background, IInteraction* interaction);
		
		void init(InteractiveInitInfo interactiveInitInfo) override;
		
		~BaseButton() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getAreaPosition() const override;
		
		sf::Vector2f getAreaSize() const override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		IScalable* background;
	};
}