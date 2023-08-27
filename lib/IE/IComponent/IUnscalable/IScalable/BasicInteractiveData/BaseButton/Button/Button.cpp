#include "Button.hpp"

namespace ie {
	Button::Make::Make(BoxPtr<IScalable::Make>&& background, BoxPtr<IBaseInteraction>&& interaction) :
		background(std::move(background)), interaction(std::move(interaction)) {
	}
	
	Button* Button::Make::make(InitInfo initInfo) {
		return new Button{std::move(*this), initInfo};
	}
	
	Button::Button(Make&& make, InitInfo initInfo) :
		BaseButton(std::move(make.background), initInfo), interactive(std::move(make.interaction), initInfo, {}) {
	}
	
	Button::Button(BoxPtr<IScalable>&& background, BoxPtr<IBaseInteraction>&& interaction) :
		BaseButton(std::move(background)), interactive(std::move(interaction)) {
	}
	
	void Button::init(InitInfo initInfo) {
		interactive.init(initInfo, {});
		BaseButton::init(initInfo);
	}
	
	Button* Button::copy() {
		return new Button{*this};
	}
	
	void Button::update() {
		interactive.update();
	}
	
	bool Button::updateInteractions(sf::Vector2f mousePosition) {
		bool result{BaseButton::updateInteractions(mousePosition)};
		interactive.updateInteractions();
		return result;
	}
	
	bool DecodePointer<Button>::decodePointer(const YAML::Node& node, Button*& button) {
		button = new Button{
			node["background"].as<BoxPtr<IScalable> >(),
			node["interaction"].as<BoxPtr<IBaseInteraction> >()
		};
		return true;
	}
}
