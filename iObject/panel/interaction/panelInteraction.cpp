#include "panelInteraction.h"

void ui::PanelInteraction::init(ui::Panel &panel, ui::PanelStack &panelStack) {
	this->panel = &panel;
	this->panelStack = &panelStack;
}
