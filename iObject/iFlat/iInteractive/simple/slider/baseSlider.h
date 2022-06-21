#pragma once
#include "../../../iDrawn/iDrawn.h"
#include "../interactiveSimple.h"
#include "interaction/interaction/sliderInteraction.h"

namespace ui {
	class BaseSlider : public Interactive_Simple {
	protected:
		IDrawn* slider;
		IDrawn* background;
		sf::Vector2f value;
		sf::Vector2f position;
		sf::Vector2f sliderSize;
		sf::Vector2f moveZoneSize;
		
		void init(sf::RenderWindow &window, PanelManager &panelManager) override;
		
		void cutBackValue();
		
		void copy(BaseSlider* baseSlider);
		
	public:
		BaseSlider(ui::IDrawn *slider, ui::IDrawn *background, SliderInteraction* interaction);
		
		sf::Vector2f getAreaSize();
		
		sf::Vector2f getSliderSize();
		
		const sf::Vector2f& getValue();
		
		void setValue(sf::Vector2f newValue);
		
		void setValueByMouse(sf::Vector2i mousePosition);
		
		void roundValueToDivision(sf::Vector2i division);
		
		bool onSlider(sf::Vector2i mousePosition);
		
		void move(sf::Vector2i mouseOffset);
		
		sf::Vector2f getPosition() override;
		
		sf::Vector2f getSize() override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override = 0;
	};
}
