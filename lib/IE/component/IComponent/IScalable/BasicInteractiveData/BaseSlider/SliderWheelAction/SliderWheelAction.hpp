#pragma once

#include "IE/interaction/BasicActionInitInfo/BasicActionInitInfo.hpp"
#include "IE/interaction/IAction/WheelAction/BaseWheelAction/BaseWheelAction.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	class BaseSlider;
	
	class SliderWheelAction : public BaseWheelAction {
	public:
		enum class Relativity {
			RelationArea,
			RelationSlider
		};
	
		struct Make {
			bool horizontal = false;
			Relativity relativity = Relativity::RelationSlider;
			sf::Vector2f sensitivity = {0.2f, 0.2f};
			
			Make(bool horizontal = false, Relativity relativity = Relativity::RelationSlider, sf::Vector2f sensitivity = {0.2f, 0.2f});
			
			SliderWheelAction* make(BasicActionInitInfo<BaseSlider&> init_info);
		};
		
		SliderWheelAction(Make&& make, BasicActionInitInfo<BaseSlider&> init_info);
		
		void set_slider(BaseSlider& slider);
		
		void start_pressed(sf::Vector2i mouse_position, int value) override;
		
		void stop_pressed(sf::Vector2i mouse_position, int value) override;
		
		void while_pressed(sf::Vector2i mouse_position, int value) override;
		
		void while_not_pressed(sf::Vector2i mouse_position, int value) override;
		
	protected:
		BaseSlider* slider_;
		sf::Vector2f sensitivity_;
		bool horizontal_;
		bool relativity_;
	};
}

template<>
struct ieml::Decode<char, ie::SliderWheelAction::Relativity> {
	static orl::Option<ie::SliderWheelAction::Relativity> decode(ieml::Node const& node);
};
