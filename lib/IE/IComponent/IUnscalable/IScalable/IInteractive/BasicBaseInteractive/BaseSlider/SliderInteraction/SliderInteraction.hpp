#pragma once

#include "IE/Interaction/IInteraction/BasicOneKeyInteraction/BasicOneKeyInteraction.hpp"
#include "IE/Interaction/IInteraction/BasicPressedInteraction/BasicPressedInteraction.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IInteractive/BasicBaseInteractive/BaseSlider/SliderAction/SliderAction.hpp"
#include "../SliderWheelAction/SliderWheelAction.hpp"

namespace ie {
	class SliderInteraction : public OneKeyInteraction {
	public:
		SliderInteraction(BaseSlider& slider, Key key, bool wheelHorizontal = false, SliderWheelAction::Relativity wheelRelativity = SliderWheelAction::Relativity::relationSlider, sf::Vector2f wheelSensitivity = {0.2f, 0.2f});
		
		SliderInteraction(BaseSlider& slider, Key key, sf::Vector2i division = {10, 10}, bool wheelHorizontal = false);
		
		SliderInteraction(BaseSlider& slider, Key key, sf::Vector2i division, bool wheelHorizontal, SliderWheelAction::Relativity wheelRelativity, sf::Vector2f wheelSensitivity);
		
		SliderInteraction(const SliderInteraction& other);
		
		void init(InteractionInitInfo initInfo) override;
		
		void setSlider(BaseSlider& slider);
		
		void update(sf::Vector2i mousePosition) override;
		
		SliderInteraction* copy() override;
	
	protected:
		SliderWheelAction wheelAction;
		PressedInteraction slideInteraction;
	};
}
