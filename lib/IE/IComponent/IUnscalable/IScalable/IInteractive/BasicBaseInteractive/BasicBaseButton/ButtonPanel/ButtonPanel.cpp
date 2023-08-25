#include "ButtonPanel.hpp"

namespace ui {
	ButtonPanel::Make::Make(BoxPtr<Panel::Make>&& panel, BoxPtr<IDisplayPanelInteraction>&& interaction, BoxPtr<IScalable::Make>&& background) :
		panel(std::move(panel)), interaction(std::move(interaction)), background(std::move(background)) {
	}
	
	ButtonPanel* ButtonPanel::Make::make(InitInfo initInfo) {
		return new ButtonPanel{std::move(*this), initInfo};
	}
	
	ButtonPanel::ButtonPanel(Make&& make, InitInfo initInfo) :
		BasicBaseButton<Panel&>(
			std::move(make.background),
			dynamicCast<IBasicInteraction<Panel&> >(std::move(make.interaction)),
			initInfo,
			*panel
		), panel(make.panel->make(initInfo)) {
		dynamic_cast<IDisplayPanelInteraction&>(*interactive.interaction).init({initInfo, *panel});
	}
	
	ButtonPanel::ButtonPanel(BoxPtr<Panel>&& panel, BoxPtr<IDisplayPanelInteraction>&& interaction, BoxPtr<IScalable>&& background) :
		BasicBaseButton<Panel&>(
			std::move(background),
			dynamicCast<IBasicInteraction<Panel&> >(std::move(interaction))
		), panel(std::move(panel)) {
	}
	
	ButtonPanel::ButtonPanel(const ButtonPanel& other) :
		BasicBaseButton<Panel&>(BoxPtr{other.background}, BoxPtr{other.interactive.interaction}), panel(BoxPtr{other.panel}) {
		dynamic_cast<IDisplayPanelInteraction&>(*interactive.interaction).setPanel(*panel);
	}
	
	void ButtonPanel::init(InitInfo initInfo) {
		BasicBaseButton<Panel&>::init(initInfo, *panel);
		panel->init(initInfo);
		dynamic_cast<IDisplayPanelInteraction&>(*interactive.interaction).init({initInfo, *panel});
	}
	
	void ButtonPanel::resize(sf::Vector2f size, sf::Vector2f position) {
		BasicBaseButton<Panel&>::resize(size, position);
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
	
	ButtonPanel* ButtonPanel::copy() {
		return new ButtonPanel{*this};
	}
	
	void ButtonPanel::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		BasicBaseButton<Panel&>::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
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
