#pragma once

#include "IE/Interaction/BasicActionInitInfo/BasicActionInitInfo.hpp"
#include "IE/Interaction/IAction/WheelAction/BaseWheelAction/BaseWheelAction.hpp"

namespace ie {
	class BaseSlider;
	
	class SliderWheelAction : public BaseWheelAction {
	public:
		enum class Relativity {
			relationArea,
			relationSlider
		};
	
		struct Make {
			bool horizontal = false;
			Relativity relativity = Relativity::relationSlider;
			sf::Vector2f sensitivity = {0.2f, 0.2f};
			
			Make(bool horizontal = false, Relativity relativity = Relativity::relationSlider, sf::Vector2f sensitivity = {0.2f, 0.2f});
			
			SliderWheelAction* make(BasicActionInitInfo<BaseSlider&> initInfo);
		};
		
		SliderWheelAction(Make&& make, BasicActionInitInfo<BaseSlider&> initInfo);
		
		explicit SliderWheelAction(bool horizontal = false, Relativity relativity = Relativity::relationSlider, sf::Vector2f sensitivity = {0.2f, 0.2f});
		
		void setSlider(BaseSlider& slider);
		
		void startPressed(sf::Vector2i mousePosition, int value) override;
		
		void stopPressed(sf::Vector2i mousePosition, int value) override;
		
		void whilePressed(sf::Vector2i mousePosition, int value) override;
		
		void whileNotPressed(sf::Vector2i mousePosition, int value) override;
		
		SliderWheelAction* copy() override;
		
	protected:
		BaseSlider* slider;
		sf::Vector2f sensitivity;
		bool horizontal;
		bool relativity;
	};
	
	template<>
	struct Decode<SliderWheelAction::Relativity> {
		static bool decode(const YAML::Node& node, SliderWheelAction::Relativity& relativity);
	};
}
