#include "buttonWithPanel.h"

ui::ButtonWithPanel::ButtonWithPanel(ui::Panel *panel, ui::DisplayPanelInteraction *interaction, ui::IFlat *background) :
	Button(background, interaction), panel(panel) {}

void ui::ButtonWithPanel::init(sf::RenderTarget &renderTarget, PanelManager &panelManager) {
	Button::init(renderTarget, panelManager);
	initObject(panel, renderTarget, *interactionStack, *interactionManager, panelManager);
	dynamic_cast<ui::DisplayPanelInteraction*>(interaction)->init(*panel, panelManager);
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
