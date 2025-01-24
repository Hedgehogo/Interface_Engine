#pragma once

#include "IE/trigger/BasicActionInitInfo/BasicActionInitInfo.hpp"
#include "IE/trigger/IAction/IBasicWheelAction/IBasicWheelAction.hpp"
#include "IE/event/EventHandler/EventHandler.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	class BaseSlider;
	
	class SliderWheelAction : public virtual IBasicWheelAction<BaseSlider&> {
	public:
		enum class Relativity {
			RelationArea,
			RelationSlider
		};
	
		struct Make : public virtual IBasicWheelAction<BaseSlider&>::Make {
			bool horizontal = false;
			Relativity relativity = Relativity::RelationSlider;
			sf::Vector2f sensitivity = {0.2f, 0.2f};
			
			Make(bool horizontal = false, Relativity relativity = Relativity::RelationSlider, sf::Vector2f sensitivity = {0.2f, 0.2f});
			
			auto make(BasicActionInitInfo<BaseSlider&> init_info) -> SliderWheelAction* override;
		};
		
		SliderWheelAction(Make&& make, BasicActionInitInfo<BaseSlider&> init_info);
		
		auto set_slider(BaseSlider& slider) -> void;
		
		auto update(int value) -> void override;
		
	protected:
		EventHandler* event_handler_;
		BaseSlider* slider_;
		sf::Vector2f sensitivity_;
		bool horizontal_;
		bool relativity_;
	};
}

template<>
struct ieml::Decode<char, ie::SliderWheelAction::Relativity> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::SliderWheelAction::Relativity>;
};
