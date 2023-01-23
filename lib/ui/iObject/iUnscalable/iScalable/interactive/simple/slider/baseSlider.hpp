#pragma once
#include "../../../uninteractive/uninteractive.hpp"
#include "../interactiveSimple.hpp"
#include "interaction/interaction/sliderInteraction.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/shared/shared.hpp"

namespace ui {
	class BaseSlider : public Interactive_Simple {
	protected:
		IUninteractive* slider;
		IUninteractive* background;
		PSRVec2f value;
		sf::Vector2f position;
		sf::Vector2f sliderSize;
		sf::Vector2f moveZoneSize;
		
		void init(InteractiveInitInfo interactiveInitInfo) override;
		
		void copy(BaseSlider* baseSlider);
		
		virtual void resizeSlider(sf::Vector2f newValue);
		
	public:
		BaseSlider(IUninteractive *slider, IUninteractive *background, const PSRVec2f &value, SliderInteraction* interaction);
		
		bool onSlider(sf::Vector2i mousePosition);
		
		sf::Vector2f getSliderSize();
		
		sf::Vector2f getValue();
		
		PSRVec2f getValuePtr();
		
		void setValue(sf::Vector2f value);
		
		void setValueByMouse(sf::Vector2i mousePosition);
		
		sf::Vector2f moveSlider(sf::Vector2f value, sf::Vector2f offset) const;
		
		static sf::Vector2f roundValueToDivision(sf::Vector2f value, sf::Vector2i division);
		
		sf::Vector2f getAreaPosition() override;
		
		sf::Vector2f getAreaSize() override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override = 0;

		BaseSlider *copy() override = 0;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
