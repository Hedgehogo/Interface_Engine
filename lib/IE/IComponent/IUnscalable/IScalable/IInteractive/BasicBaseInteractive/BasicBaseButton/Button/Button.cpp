#include "Button.hpp"

namespace ui {
	Button::Make::Make(BoxPtr<IScalable::Make>&& background, BoxPtr<IBaseInteraction>&& interaction) :
		background(std::move(background)), interaction(std::move(interaction)){
	}
	
	Button* Button::Make::make(InitInfo initInfo) {
		return new Button{std::move(*this), initInfo};
	}
	
	Button::Button(Make&& make, InitInfo initInfo) :
		BaseButton(std::move(make.background), std::move(make.interaction), initInfo, {}),
		interactionIndex(std::numeric_limits<std::size_t>::max()) {
	}
	
	Button::Button(BoxPtr<IScalable>&& background, BoxPtr<IBaseInteraction>&& interaction) :
		BaseButton(std::move(background), std::move(interaction)), interactionIndex(std::numeric_limits<std::size_t>::max()) {
	}
	
	void Button::init(InitInfo initInfo) {
		BaseButton::init(initInfo, {});
	}
	
	Button* Button::copy() {
		return new Button{*this};
	}
	
	bool DecodePointer<Button>::decodePointer(const YAML::Node& node, Button*& button) {
		button = new Button{
			node["background"].as<BoxPtr<IScalable> >(),
			node["interaction"].as<BoxPtr<IBaseInteraction> >()
		};
		return true;
	}
}
