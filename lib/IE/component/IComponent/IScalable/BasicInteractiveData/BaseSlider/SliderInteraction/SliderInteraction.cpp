#include "SliderInteraction.hpp"
#include "IE/interaction/IAction/IBasicActivityAction/BasicAddInteractionAction/BasicAddPrioritisedInteractionAction/BasicAddPrioritisedInteractionAction.hpp"

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
		BasicAnyPressingInteraction<BaseSlider&>(
			{
				make_box_ptr<BasicAddPrioritisedInteractionAction<BaseSlider&>::Make>(
					make_box_ptr<BasicTouchInteraction<BaseSlider&>::Make, BasicPressedInteraction<BaseSlider&>::Make>(
						make_box_ptr<SliderAction::Make>(make.division), make.key
					)
				), make.key
			}, init_info
		),
		wheel_action_({make.wheel_horizontal, make.wheel_relativity, make.wheel_sensitivity}, init_info) {
	}
	
	auto SliderInteraction::update() -> void {
		wheel_action_.update(MouseWheel::get_delta().y);
		BasicAnyPressingInteraction<BaseSlider&>::update();
	}
}
