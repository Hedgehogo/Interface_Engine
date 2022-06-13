#include "buttonWithPanel.h"

ui::ButtonWithPanel::ButtonWithPanel(ui::Panel *panel, ui::DisplayPanelInteraction *interaction, ui::IFlat *background) :
	Button(background, interaction), panel(panel) {}

void ui::ButtonWithPanel::init(sf::RenderWindow &window, ui::Panel *parent, ui::PanelStack &panelStack) {
	Button::init(window, parent, panelStack);
	initObject(panel, window, *interactionStack, *interactionManager, parent, panelStack);
	dynamic_cast<ui::DisplayPanelInteraction*>(interaction)->init(*panel, panelStack);
}

ui::ButtonWithPanel::~ButtonWithPanel() {
	delete panel;
	delete interaction;
}

void ui::ButtonWithPanel::resize(sf::Vector2f size, sf::Vector2f position) {
	Button::resize(size, position);
	panel->resize(size, position);
}

ui::ButtonWithPanel *ui::ButtonWithPanel::copy() {
	Panel* panel1{panel->copy()};
	DisplayPanelInteraction* displayPanelInteraction{dynamic_cast<ui::DisplayPanelInteraction*>(interaction)->copy()};
	displayPanelInteraction->setPanel(*panel1);
	ButtonWithPanel* buttonWithPanel{new ButtonWithPanel{panel1, displayPanelInteraction, background->copy()}};
	Button::copy(buttonWithPanel);
	return buttonWithPanel;
}
