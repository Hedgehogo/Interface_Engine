#include "panelInteraction.h"

void ui::PanelInteraction::init(ui::Panel &panel, ui::PanelStack &panelStack) {
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
