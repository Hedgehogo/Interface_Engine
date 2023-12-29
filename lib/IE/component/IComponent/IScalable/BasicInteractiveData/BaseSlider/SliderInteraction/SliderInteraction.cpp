#include "SliderInteraction.hpp"
#include "IE/interaction/IAction/BasicKeyAction/BasicAddInteractionAction/BasicAddBlockInteractionAction/BasicAddBlockInteractionAction.hpp"

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
	
	SliderInteraction* SliderInteraction::Make::make(BasicActionInitInfo<BaseSlider&> init_info) {
		return new SliderInteraction{std::move(*this), init_info};
	}
	
	SliderInteraction::SliderInteraction(Make&& make, BasicActionInitInfo<BaseSlider&> init_info) :
		BasicOneKeyInteraction<BaseSlider&>(
			{
				make_box_ptr<BasicAddBlockInteractionAction<BaseSlider&>::Make>(
					make_box_ptr<BasicOneKeyInteraction<BaseSlider&>::Make, BasicPressedInteraction<BaseSlider&>::Make>(
						make_box_ptr<SliderAction::Make>(make.division), make.key
					)
				), make.key
			}, init_info
		),
		wheel_action_({make.wheel_horizontal, make.wheel_relativity, make.wheel_sensitivity}, init_info) {
	}
	
	SliderInteraction::SliderInteraction(
		Key key,
		sf::Vector2i division,
		bool wheel_horizontal,
		SliderWheelAction::Relativity wheel_relativity,
		sf::Vector2f wheel_sensitivity
	) :
		BasicOneKeyInteraction<BaseSlider&>(
			make_box_ptr<BasicAddBlockInteractionAction<BaseSlider&> >(
				make_box_ptr<BasicPressedInteraction<BaseSlider&> >(
					make_box_ptr<SliderAction>(division), key
				)
			), key
		),
		wheel_action_(wheel_horizontal, wheel_relativity, wheel_sensitivity) {
	}
	
	SliderInteraction::SliderInteraction(Key key, bool wheel_horizontal, SliderWheelAction::Relativity wheel_relativity, sf::Vector2f wheel_sensitivity) :
		SliderInteraction(key, {}, wheel_horizontal, wheel_relativity, wheel_sensitivity) {
	}
	
	SliderInteraction::SliderInteraction(Key key, sf::Vector2i division, bool wheel_horizontal) :
		SliderInteraction(
			key,
			division,
			wheel_horizontal,
			SliderWheelAction::Relativity::RelationArea,
			{1.0f / static_cast<float>(division.x), 1.0f / static_cast<float>(division.y)}
		) {
	}
	
	void SliderInteraction::set_slider(BaseSlider& slider) {
		auto& slide_action{dynamic_cast<BasicAddBlockInteractionAction<BaseSlider&>&>(*action_)};
		auto& slide_interaction{dynamic_cast<BasicPressedInteraction<BaseSlider&>&>(slide_action.get_interaction())};
		dynamic_cast<SliderAction&>(slide_interaction.get_action()).set_slider(slider);
		wheel_action_.set_slider(slider);
	}
	
	void SliderInteraction::update(sf::Vector2i mouse_position) {
		wheel_action_.update(mouse_position, MouseWheel::get_delta().y);
		return BasicOneKeyInteraction<BaseSlider&>::update(mouse_position);
	}
	
	SliderInteraction* SliderInteraction::copy() {
		return new SliderInteraction{*this};
	}
}