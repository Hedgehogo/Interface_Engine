#include "SliderInteraction.hpp"
#include "IE/Interaction/IAction/BasicKeyAction/BasicAddInteractionAction/BasicAddBlockInteractionAction/BasicAddBlockInteractionAction.hpp"

namespace ie {
	SliderInteraction::Make::Make(
		Key key,
		sf::Vector2i division,
		bool wheelHorizontal,
		SliderWheelAction::Relativity wheelRelativity,
		sf::Vector2f wheelSensitivity
	) :
		key(key), division(division), wheelHorizontal(wheelHorizontal), wheelRelativity(wheelRelativity), wheelSensitivity(wheelSensitivity) {
	}
	
	SliderInteraction::Make::Make(Key key, bool wheelHorizontal, SliderWheelAction::Relativity wheelRelativity, sf::Vector2f wheelSensitivity) :
		key(key), division(), wheelHorizontal(wheelHorizontal), wheelRelativity(wheelRelativity), wheelSensitivity(wheelSensitivity) {
	}
	
	SliderInteraction::Make::Make(Key key, sf::Vector2i division, bool wheelHorizontal) :
		key(key),
		division(division),
		wheelHorizontal(wheelHorizontal),
		wheelRelativity(SliderWheelAction::Relativity::relationArea),
		wheelSensitivity({1.0f / static_cast<float>(division.x), 1.0f / static_cast<float>(division.y)}) {
	}
	
	SliderInteraction* SliderInteraction::Make::make(BasicActionInitInfo<BaseSlider&> initInfo) {
		return new SliderInteraction{std::move(*this), initInfo};
	}
	
	SliderInteraction::SliderInteraction(Make&& make, BasicActionInitInfo<BaseSlider&> initInfo) :
		BasicOneKeyInteraction<BaseSlider&>(
			{
				makeBoxPtr<BasicKeyAction<BaseSlider&>, BasicAddBlockInteractionAction<BaseSlider&> >(
					makeBoxPtr<IBasicInteraction<BaseSlider&>, BasicPressedInteraction<BaseSlider&> >(
						makeBoxPtr<BasicKeyAction<BaseSlider&>, SliderAction>(make.division), make.key
					)
				), make.key
			}, initInfo
		),
		wheelAction({make.wheelHorizontal, make.wheelRelativity, make.wheelSensitivity}, initInfo) {
	}
	
	SliderInteraction::SliderInteraction(
		Key key,
		sf::Vector2i division,
		bool wheelHorizontal,
		SliderWheelAction::Relativity wheelRelativity,
		sf::Vector2f wheelSensitivity
	) :
		BasicOneKeyInteraction<BaseSlider&>(
			makeBoxPtr<BasicAddBlockInteractionAction<BaseSlider&> >(
				makeBoxPtr<BasicPressedInteraction<BaseSlider&> >(
					makeBoxPtr<SliderAction>(division), key
				)
			), key
		),
		wheelAction(wheelHorizontal, wheelRelativity, wheelSensitivity) {
	}
	
	SliderInteraction::SliderInteraction(Key key, bool wheelHorizontal, SliderWheelAction::Relativity wheelRelativity, sf::Vector2f wheelSensitivity) :
		SliderInteraction(key, {}, wheelHorizontal, wheelRelativity, wheelSensitivity) {
	}
	
	SliderInteraction::SliderInteraction(Key key, sf::Vector2i division, bool wheelHorizontal) :
		SliderInteraction(
			key,
			division,
			wheelHorizontal,
			SliderWheelAction::Relativity::relationArea,
			{1.0f / static_cast<float>(division.x), 1.0f / static_cast<float>(division.y)}
		) {
	}
	
	void SliderInteraction::setSlider(BaseSlider& slider) {
		auto& slideAction{dynamic_cast<BasicAddBlockInteractionAction<BaseSlider&>&>(*action)};
		auto& slideInteraction{dynamic_cast<BasicPressedInteraction<BaseSlider&>&>(slideAction.getInteraction())};
		dynamic_cast<SliderAction&>(slideInteraction.getAction()).setSlider(slider);
		wheelAction.setSlider(slider);
	}
	
	void SliderInteraction::update(sf::Vector2i mousePosition) {
		wheelAction.update(mousePosition, MouseWheel::getDelta().y);
		return BasicOneKeyInteraction<BaseSlider&>::update(mousePosition);
	}
	
	SliderInteraction* SliderInteraction::copy() {
		return new SliderInteraction{*this};
	}
}
