#include "panelEvent.h"

ui::PanelEvent::PanelEvent() : panel(nullptr), panelManager(nullptr) {}

void ui::PanelEvent::init(ui::Panel &panel, ui::PanelManager &panelStack) {
	this->panel = &panel;
	this->panelManager = &panelStack;
}

void ui::PanelEvent::setPanel(ui::Panel &panel) {
	this->panel = &panel;
}

void ui::PanelEvent::copy(ui::PanelEvent *panelEvent) {
	panelEvent->panel = this->panel;
	panelEvent->panelManager = this->panelManager;
}
