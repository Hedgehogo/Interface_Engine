#include "button.hpp"

namespace ui {
	Button::Make::Make(BoxPtr<IScalable::Make>&& background, BoxPtr<IInteraction>&& interaction) :
		background(std::move(background)), interaction(std::move(interaction)){
	}
	
	Button* Button::Make::make(InitInfo initInfo) {
		return new Button{std::move(*this), initInfo};
	}
	
	Button::Button(Make&& make, InitInfo initInfo) :
		BaseButton(std::move(make.background), std::move(make.interaction), initInfo),
		interactionIndex(std::numeric_limits<std::size_t>::max()) {
	}
	
	Button::Button(BoxPtr<IScalable>&& background, std::size_t interaction) :
		BaseButton(std::move(background), BoxPtr<IInteraction>{nullptr}), interactionIndex(interaction) {
	}
	
	Button::Button(BoxPtr<IScalable>&& background, BoxPtr<IInteraction>&& interaction) :
		BaseButton(std::move(background), std::move(interaction)), interactionIndex(std::numeric_limits<std::size_t>::max()) {
	}
	
	Button::~Button() {
		if(interactionIndex != std::numeric_limits<std::size_t>::max()) {
			interactive.interaction.set(nullptr);
		}
	}
	
	void Button::init(InitInfo initInfo) {
		BaseButton::init(initInfo);
		if(interactionIndex != std::numeric_limits<std::size_t>::max()) {
			interactive.interaction = BoxPtr{&interactive.interactionStack->at(interactionIndex)};
		}
	}
	
	Button* Button::copy() {
		return new Button{*this};
	}
	
	bool DecodePointer<Button>::decodePointer(const YAML::Node& node, Button*& button) {
		auto background{node["background"].as<BoxPtr<IScalable> >()};
		
		if(node["interaction"]) {
			button = new Button{
				std::move(background),
				node["interaction"].as<BoxPtr<IInteraction> >()
			};
		} else {
			button = new Button{
				std::move(background),
				node["index"].as<std::size_t>()
			};
		}
		return true;
	}
}
