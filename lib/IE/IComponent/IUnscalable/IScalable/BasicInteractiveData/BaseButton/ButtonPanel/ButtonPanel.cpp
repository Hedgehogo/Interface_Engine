#include "ButtonPanel.hpp"

namespace ie {
	ButtonPanel::Make::Make(BoxPtr<Panel::Make>&& panel, BoxPtr<IDisplayPanelInteraction::Make>&& interaction, BoxPtr<IScalable::Make>&& background) :
		panel(std::move(panel)), interaction(std::move(interaction)), background(std::move(background)) {
	}
	
	ButtonPanel* ButtonPanel::Make::make(InitInfo initInfo) {
		return new ButtonPanel{std::move(*this), initInfo};
	}
	
	ButtonPanel::ButtonPanel(Make&& make, InitInfo initInfo) :
		BaseButton(std::move(make.background), initInfo),
		panel(make.panel->make(initInfo)),
		interactive(std::move(make.interaction), initInfo, *panel) {
	}
	
	ButtonPanel::ButtonPanel(BoxPtr<Panel>&& panel, BoxPtr<IDisplayPanelInteraction>&& interaction, BoxPtr<IScalable>&& background) :
		BaseButton(std::move(background)),
		panel(std::move(panel)),
		interactive(std::move(interaction)) {
	}
	
	ButtonPanel::ButtonPanel(const ButtonPanel& other) :
		BaseButton(BoxPtr{other.background}),
		panel(other.panel),
		interactive(other.interactive) {
		dynamic_cast<IDisplayPanelInteraction&>(*interactive.interaction).setPanel(*panel);
	}
	
	void ButtonPanel::init(InitInfo initInfo) {
		BaseButton::init(initInfo);
		panel->init(initInfo);
		dynamic_cast<IDisplayPanelInteraction&>(*interactive.interaction).init({initInfo, *panel});
	}
	
	void ButtonPanel::resize(sf::Vector2f size, sf::Vector2f position) {
		BaseButton::resize(size, position);
		panel->resize(size, position);
	}
	
	sf::Vector2f ButtonPanel::getMinSize() const {
		sf::Vector2f backgroundMinSize{background->getMinSize()};
		sf::Vector2f panelMinSize{panel->getMinSize()};
		return {std::max(backgroundMinSize.x, panelMinSize.x), std::max(backgroundMinSize.y, panelMinSize.y)};
	}
	
	const Panel& ButtonPanel::getPanel() const {
		return *panel;
	}
	
	void ButtonPanel::update() {
		interactive.update();
	}
	
	bool ButtonPanel::updateInteractions(sf::Vector2f mousePosition) {
		bool result{BaseButton::updateInteractions(mousePosition)};
		interactive.updateInteractions();
		return result;
	}
	
	ButtonPanel* ButtonPanel::copy() {
		return new ButtonPanel{*this};
	}
	
	void ButtonPanel::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		BaseButton::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		panel->drawDebug(renderTarget, 0, indentAddition, hue, hueOffset);
	}
	
	bool DecodePointer<ButtonPanel>::decodePointer(const YAML::Node& node, ButtonPanel*& buttonWithPanel) {
		buttonWithPanel = new ButtonPanel{
			node["panel"].as<BoxPtr<Panel> >(),
			node["display-interaction"].as<BoxPtr<IDisplayPanelInteraction> >(),
			node["background"].as<BoxPtr<IScalable> >()
		};
		return true;
	}
}
