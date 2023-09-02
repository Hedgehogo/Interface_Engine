#pragma once

#include "IE/IComponent/IUnscalable/IScalable/IUninteractive/IUninteractive.hpp"
#include "../BasicInteractiveData.hpp"
#include "SliderInteraction/SliderInteraction.hpp"
#include "../../../../../Modules/yaml-cpp/shared/shared.hpp"

namespace ie {
	class BaseSlider : public virtual IScalable, public IUpdatable {
	public:
		BaseSlider(
			BoxPtr<IUninteractive::Make>&& slider,
			BoxPtr<IUninteractive::Make>&& background,
			BoxPtr<SliderInteraction::Make>&& interaction,
			const PSRVec2f& value,
			InitInfo initInfo
		);
		
		BaseSlider(
			BoxPtr<IUninteractive>&& slider,
			BoxPtr<IUninteractive>&& background,
			BoxPtr<SliderInteraction>&& interaction,
			const PSRVec2f& value
		);
		
		BaseSlider(const BaseSlider& other);
		
		void init(InitInfo initInfo) override;
		
		bool onSlider(sf::Vector2i mousePosition);
		
		sf::Vector2f getSliderSize();
		
		sf::Vector2f getValue();
		
		PSRVec2f getValuePtr();
		
		void setValue(sf::Vector2f value);
		
		void setValueByMouse(sf::Vector2i mousePosition);
		
		sf::Vector2f moveSlider(sf::Vector2f value, sf::Vector2f offset) const;
		
		static sf::Vector2f roundValueToDivision(sf::Vector2f value, sf::Vector2i division);
		
		sf::Vector2f getAreaPosition() const override;
		
		sf::Vector2f getAreaSize() const override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override = 0;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		BaseSlider* copy() override = 0;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		virtual void resizeSlider(sf::Vector2f newValue);
		
		BasicInteractiveData<BaseSlider&> interactive;
		BoxPtr<IUninteractive> background;
		BoxPtr<IUninteractive> slider;
		PSRVec2f value;
		sf::Vector2f position;
		sf::Vector2f sliderSize;
		sf::Vector2f moveZoneSize;
	};
}