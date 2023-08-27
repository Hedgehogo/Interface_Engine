#pragma once

#include "IE/Interaction/IInteraction/BasicOneKeyInteraction/BasicOneKeyInteraction.hpp"
#include "IE/Interaction/IInteraction/BasicPressedInteraction/BasicPressedInteraction.hpp"
#include "IE/IComponent/IUnscalable/IScalable/BasicInteractiveData/BaseSlider/SliderAction/SliderAction.hpp"
#include "../SliderWheelAction/SliderWheelAction.hpp"

namespace ie {
	class SliderInteraction : public BasicOneKeyInteraction<BaseSlider&> {
	public:
		struct Make : public IBasicInteraction<BaseSlider&>::Make {
			Key key;
			sf::Vector2i division;
			bool wheelHorizontal;
			SliderWheelAction::Relativity wheelRelativity;
			sf::Vector2f wheelSensitivity;
			
			Make(Key key, sf::Vector2i division, bool wheelHorizontal, SliderWheelAction::Relativity wheelRelativity, sf::Vector2f wheelSensitivity);
			
			Make(
				Key key,
				bool wheelHorizontal = false,
				SliderWheelAction::Relativity wheelRelativity = SliderWheelAction::Relativity::relationSlider,
				sf::Vector2f wheelSensitivity = {0.2f, 0.2f}
			);
			
			Make(Key key, sf::Vector2i division = {10, 10}, bool wheelHorizontal = false);
			
			SliderInteraction* make(BasicActionInitInfo<BaseSlider&> initInfo) override;
		};
		
		SliderInteraction(Make&& make, BasicActionInitInfo<BaseSlider&> initInfo);
		
		SliderInteraction(
			Key key,
			bool wheelHorizontal = false,
			SliderWheelAction::Relativity wheelRelativity = SliderWheelAction::Relativity::relationSlider,
			sf::Vector2f wheelSensitivity = {0.2f, 0.2f}
		);
		
		SliderInteraction(Key key, sf::Vector2i division = {10, 10}, bool wheelHorizontal = false);
		
		SliderInteraction(Key key, sf::Vector2i division, bool wheelHorizontal, SliderWheelAction::Relativity wheelRelativity, sf::Vector2f wheelSensitivity);
		
		void setSlider(BaseSlider& slider);
		
		void update(sf::Vector2i mousePosition) override;
		
		SliderInteraction* copy() override;
	
	protected:
		SliderWheelAction wheelAction;
	};
}
