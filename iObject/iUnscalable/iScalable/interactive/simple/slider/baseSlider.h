#pragma once
#include "../../../iDrawable/iDrawable.h"
#include "../interactiveSimple.h"
#include "interaction/interaction/sliderInteraction.h"

namespace ui {
	class BaseSlider : public Interactive_Simple {
	protected:
		IDrawable* slider;
		IDrawable* background;
		sf::Vector2f value;
		sf::Vector2f position;
		sf::Vector2f sliderSize;
		sf::Vector2f moveZoneSize;
		
		void init(sf::RenderTarget &renderTarget, PanelManager &panelManager) override;
		
		void cutBackValue();
		
		void copy(BaseSlider* baseSlider);
		
	public:
		BaseSlider(ui::IDrawable *slider, ui::IDrawable *background, SliderInteraction* interaction);
		
		sf::Vector2f getSliderSize();
		
		const sf::Vector2f& getValue();
		
		void setValue(sf::Vector2f newValue);
		
		void setValueByMouse(sf::Vector2i mousePosition);
		
		void roundValueToDivision(sf::Vector2i division);
		
		bool onSlider(sf::Vector2i mousePosition);
		
		void moveSlider(sf::Vector2i mouseOffset);
		
		sf::Vector2f getAreaPosition() override;
		
		sf::Vector2f getAreaSize() override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override = 0;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
