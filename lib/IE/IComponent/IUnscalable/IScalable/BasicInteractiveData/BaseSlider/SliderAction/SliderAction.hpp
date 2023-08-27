#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"

namespace ie {
	class BaseSlider;
	
	class SliderAction : public BasicBaseKeyAction<BaseSlider&> {
	protected:
		sf::Vector2f getMousePosition();
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		explicit SliderAction(sf::Vector2i division = {0, 0});
		
		void init(BasicActionInitInfo<BaseSlider&> initInfo) override;
		
		void setSlider(BaseSlider& slider);
		
		SliderAction* copy() override;
	
	protected:
		BaseSlider* slider;
		sf::Vector2i startMousePosition;
		sf::Vector2f startValue;
		sf::Vector2i division;
	};
}
