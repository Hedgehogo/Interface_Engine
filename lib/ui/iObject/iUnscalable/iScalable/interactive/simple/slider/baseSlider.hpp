#pragma once
#include "../../../uninteractive/unIteractive.hpp"
#include "../interactiveSimple.hpp"
#include "interaction/interaction/sliderInteraction.hpp"
#include "../../../../../../with/vector/general/withVector2.hpp"

namespace ui {
	class BaseSlider : public Interactive_Simple, public IDrawable {
	protected:
		IUninteractive* slider;
		IUninteractive* background;
		std::shared_ptr<WithCoefficientVec2> value;
		sf::Vector2f position;
		sf::Vector2f sliderSize;
		sf::Vector2f moveZoneSize;
		
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, PanelManager &panelManager) override;
		
		void cutBackValue();
		
		void copy(BaseSlider* baseSlider);
		
	public:
		BaseSlider(ui::IUninteractive *slider, ui::IUninteractive *background, const std::shared_ptr<WithCoefficientVec2>& value, SliderInteraction* interaction);
		
		sf::Vector2f getSliderSize();
		
		sf::Vector2f getValue();
		
		void setValue(sf::Vector2f value);
		
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
