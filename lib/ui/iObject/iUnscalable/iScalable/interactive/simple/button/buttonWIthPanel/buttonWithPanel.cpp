#include "buttonWithPanel.hpp"

ui::ButtonWithPanel::ButtonWithPanel(ui::Panel *panel, ui::DisplayPanelInteraction *interaction, ui::IScalable *background) :
    BaseButton(background, interaction), panel(panel) {}

void ui::ButtonWithPanel::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, IPanelManager &panelManager) {
	BaseButton::init(renderTarget, drawManager, updateManager, panelManager);
	panel->init(renderTarget, drawManager, updateManager, *interactionManager, *interactionStack, panelManager);
	dynamic_cast<ui::DisplayPanelInteraction*>(interaction)->init(*panel, panelManager);
}

ui::ButtonWithPanel::~ButtonWithPanel() {
	delete panel;
	delete interaction;
}

void ui::ButtonWithPanel::resize(sf::Vector2f size, sf::Vector2f position) {
	BaseButton::resize(size, position);
	panel->resize(size, position);
}

sf::Vector2f ui::ButtonWithPanel::getMinSize() {
	sf::Vector2f backgroundMinSize {background->getMinSize()};
	sf::Vector2f panelMinSize {panel->getMinSize()};
	return {std::max(backgroundMinSize.x, panelMinSize.x), std::max(backgroundMinSize.y, panelMinSize.y)};
}

ui::ButtonWithPanel *ui::ButtonWithPanel::copy() {
	Panel* panel1{panel->copy()};
	DisplayPanelInteraction* displayPanelInteraction{dynamic_cast<ui::DisplayPanelInteraction*>(interaction)->copy()};
	displayPanelInteraction->setPanel(*panel1);
	ButtonWithPanel* buttonWithPanel{new ButtonWithPanel{panel1, displayPanelInteraction, background->copy()}};
	BaseButton::copy(buttonWithPanel);
	return buttonWithPanel;
}

void ui::ButtonWithPanel::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
    BaseButton::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
    panel->drawDebug(renderTarget, 0, indentAddition, hue, hueOffset);
}

ui::ButtonWithPanel *ui::ButtonWithPanel::createFromYaml(const YAML::Node &node) {
	Panel *panel;
	DisplayPanelInteraction* interaction;
	IScalable *background;
	
	node["panel"] >> panel;
	node["display-interaction"] >> interaction;
	node["background"] >> background;
	
	return new ButtonWithPanel{panel, interaction, background};
}
