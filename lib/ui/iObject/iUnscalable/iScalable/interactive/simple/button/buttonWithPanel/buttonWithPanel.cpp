#include "buttonWithPanel.hpp"

namespace ui {
	ButtonWithPanel::ButtonWithPanel(Panel* panel, DisplayPanelInteraction* interaction, IScalable* background) :
		BaseButton(background, interaction), panel(panel) {
	}
	
	void ButtonWithPanel::init(InteractiveInitInfo interactiveInitInfo) {
		BaseButton::init(interactiveInitInfo);
		panel->init(interactiveInitInfo.toGeneral(*interactionManager, *interactionStack));
		dynamic_cast<DisplayPanelInteraction*>(interaction)->init(*panel, interactiveInitInfo.panelManager);
	}
	
	ButtonWithPanel::~ButtonWithPanel() {
		delete panel;
		delete interaction;
	}
	
	void ButtonWithPanel::resize(sf::Vector2f size, sf::Vector2f position) {
		BaseButton::resize(size, position);
		panel->resize(size, position);
	}
	
	sf::Vector2f ButtonWithPanel::getMinSize() {
		sf::Vector2f backgroundMinSize{background->getMinSize()};
		sf::Vector2f panelMinSize{panel->getMinSize()};
		return {std::max(backgroundMinSize.x, panelMinSize.x), std::max(backgroundMinSize.y, panelMinSize.y)};
	}
	
	ButtonWithPanel* ButtonWithPanel::copy() {
		Panel* panel1{panel->copy()};
		DisplayPanelInteraction* displayPanelInteraction{dynamic_cast<DisplayPanelInteraction*>(interaction)->copy()};
		displayPanelInteraction->setPanel(*panel1);
		ButtonWithPanel* buttonWithPanel{new ButtonWithPanel{panel1, displayPanelInteraction, background->copy()}};
		BaseButton::copy(buttonWithPanel);
		return buttonWithPanel;
	}
	
	void ButtonWithPanel::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		BaseButton::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		panel->drawDebug(renderTarget, 0, indentAddition, hue, hueOffset);
	}
	
	
	bool DecodePointer<ButtonWithPanel>::decodePointer(const YAML::Node& node, ButtonWithPanel*& buttonWithPanel) {
		Panel* panel;
		DisplayPanelInteraction* interaction;
		IScalable* background;
		
		node["panel"] >> panel;
		node["display-interaction"] >> interaction;
		node["background"] >> background;
		
		{
			buttonWithPanel = new ButtonWithPanel{panel, interaction, background};
			return true;
		}
	}
}
