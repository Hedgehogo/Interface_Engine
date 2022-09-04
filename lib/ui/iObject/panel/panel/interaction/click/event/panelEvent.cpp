#include "panelEvent.hpp"

ui::PanelEvent::PanelEvent() : panel(nullptr), panelManager(nullptr) {}

void ui::PanelEvent::init(ui::Panel &panel, ui::PanelManager &panelManager) {
	this->panel = &panel;
	this->panelManager = &panelManager;
}

void ui::PanelEvent::setPanel(ui::Panel &panel) {
	this->panel = &panel;
}

void ui::PanelEvent::copy(ui::PanelEvent *panelEvent) {
	panelEvent->panel = this->panel;
	panelEvent->panelManager = this->panelManager;
}

ui::Panel *ui::PanelEvent::getPanel() {
	return panel;
}
