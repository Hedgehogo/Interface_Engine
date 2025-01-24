#include "SliderTrigger.hpp"

namespace ie {
	SliderTrigger::Make::Make(
		Key key,
		sf::Vector2i division,
		bool wheel_horizontal,
		SliderWheelAction::Relativity wheel_relativity,
		sf::Vector2f wheel_sensitivity
	) :
		key(key), division(division), wheel_horizontal(wheel_horizontal), wheel_relativity(wheel_relativity), wheel_sensitivity(wheel_sensitivity) {
	}
	
	SliderTrigger::Make::Make(Key key, bool wheel_horizontal, SliderWheelAction::Relativity wheel_relativity, sf::Vector2f wheel_sensitivity) :
		key(key), division(), wheel_horizontal(wheel_horizontal), wheel_relativity(wheel_relativity), wheel_sensitivity(wheel_sensitivity) {
	}
	
	SliderTrigger::Make::Make(Key key, sf::Vector2i division, bool wheel_horizontal) :
		key(key),
		division(division),
		wheel_horizontal(wheel_horizontal),
		wheel_relativity(SliderWheelAction::Relativity::RelationArea),
		wheel_sensitivity({1.0f / static_cast<float>(division.x), 1.0f / static_cast<float>(division.y)}) {
	}
	
	auto SliderTrigger::Make::make(BasicActionInitInfo<BaseSlider&> init_info) -> SliderTrigger* {
		return new SliderTrigger{std::move(*this), init_info};
	}
	
	SliderTrigger::SliderTrigger(Make&& make, BasicActionInitInfo<BaseSlider&> init_info) :
		BasicActiveTrigger<BaseSlider&>(
			{
				make_box_ptr<BasicTouchTrigger<BaseSlider&>::Make>(
					make_box_ptr<SliderAction::Make>(make.division), make.key
				)
			}, init_info
		),
		wheel_action_({make.wheel_horizontal, make.wheel_relativity, make.wheel_sensitivity}, init_info) {
	}
	
	auto SliderTrigger::handle_event(Event event) -> bool {
		return
			BasicActiveTrigger<BaseSlider&>::handle_event(event) ||
			event.scroll().map([this](event_system::Scroll scroll) {
				if(scroll.wheel_id == 0) {
					delta_ = scroll.delta;
					return true;
				}
				return true;
			}).some_or(false);
	}
	
	auto SliderTrigger::update() -> void {
		wheel_action_.update(delta_);
		BasicActiveTrigger<BaseSlider&>::update();
	}
}
