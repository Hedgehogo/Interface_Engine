#include "panelInteraction.h"

ui::PanelInteraction::PanelInteraction() : panel(nullptr), panelStack(nullptr) {}

void ui::PanelInteraction::init(ui::Panel &panel, ui::PanelManager &panelStack) {
	this->panel = &panel;
	this->panelStack = &panelStack;
}

void ui::PanelInteraction::setPanel(ui::Panel &panel) {
	this->panel = &panel;
}

void ui::PanelInteraction::copy(ui::PanelInteraction *panelInteraction) {
	panelInteraction->panel = this->panel;
	panelInteraction->panelStack = this->panelStack;
}
