#include "panelInteraction.h"

ui::PanelInteraction::PanelInteraction() : panel(nullptr), panelManager(nullptr) {}

void ui::PanelInteraction::init(ui::Panel &panel, ui::PanelManager &panelManager) {
	this->panel = &panel;
	this->panelManager = &panelManager;
}

void ui::PanelInteraction::setPanel(ui::Panel &panel) {
	this->panel = &panel;
}

void ui::PanelInteraction::copy(ui::PanelInteraction *panelInteraction) {
	panelInteraction->panel = this->panel;
	panelInteraction->panelManager = this->panelManager;
}
