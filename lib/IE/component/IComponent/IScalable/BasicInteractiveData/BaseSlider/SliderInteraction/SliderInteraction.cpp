#include "SliderInteraction.hpp"

namespace ie {
	SliderInteraction::Make::Make(
		Key key,
		sf::Vector2i division,
		bool wheel_horizontal,
		SliderWheelAction::Relativity wheel_relativity,
		sf::Vector2f wheel_sensitivity
	) :
		key(key), division(division), wheel_horizontal(wheel_horizontal), wheel_relativity(wheel_relativity), wheel_sensitivity(wheel_sensitivity) {
	}
	
	SliderInteraction::Make::Make(Key key, bool wheel_horizontal, SliderWheelAction::Relativity wheel_relativity, sf::Vector2f wheel_sensitivity) :
		key(key), division(), wheel_horizontal(wheel_horizontal), wheel_relativity(wheel_relativity), wheel_sensitivity(wheel_sensitivity) {
	}
	
	SliderInteraction::Make::Make(Key key, sf::Vector2i division, bool wheel_horizontal) :
		key(key),
		division(division),
		wheel_horizontal(wheel_horizontal),
		wheel_relativity(SliderWheelAction::Relativity::RelationArea),
		wheel_sensitivity({1.0f / static_cast<float>(division.x), 1.0f / static_cast<float>(division.y)}) {
	}
	
	auto SliderInteraction::Make::make(BasicActionInitInfo<BaseSlider&> init_info) -> SliderInteraction* {
		return new SliderInteraction{std::move(*this), init_info};
	}
	
	SliderInteraction::SliderInteraction(Make&& make, BasicActionInitInfo<BaseSlider&> init_info) :
		BasicActiveInteraction<BaseSlider&>(
			{
				make_box_ptr<BasicTouchInteraction<BaseSlider&>::Make>(
					make_box_ptr<SliderAction::Make>(make.division), make.key
				)
			}, init_info
		),
		wheel_action_({make.wheel_horizontal, make.wheel_relativity, make.wheel_sensitivity}, init_info) {
	}
	
	auto SliderInteraction::handle_event(Event event) -> bool {
		return
			BasicActiveInteraction<BaseSlider&>::handle_event(event) ||
			event.scroll().map([this](event_system::Scroll scroll) {
				if(scroll.wheel_id == 0) {
					delta_ = scroll.delta;
					return true;
				}
				return true;
			}).some_or(false);
	}
	
	auto SliderInteraction::update() -> void {
		wheel_action_.update(delta_);
		BasicActiveInteraction<BaseSlider&>::update();
	}
}
