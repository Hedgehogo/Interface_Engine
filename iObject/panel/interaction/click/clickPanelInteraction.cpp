#include "clickPanelInteraction.h"

ui::ClickPanelInteraction::ClickPanelInteraction(ui::PanelEvent *event, sf::Mouse::Button button) : OneButtonInteraction(event, button), BasePanelInteraction() {}

void ui::ClickPanelInteraction::init(ui::Panel &panel, ui::PanelManager &panelStack) {
	dynamic_cast<ui::PanelEvent*>(event)->init(panel, panelStack);
}

void ui::ClickPanelInteraction::setPanel(ui::Panel &panel) {
	dynamic_cast<ui::PanelEvent*>(event)->setPanel(panel);
}

ui::ClickPanelInteraction *ui::ClickPanelInteraction::copy() {
	return new ClickPanelInteraction{dynamic_cast<ui::PanelEvent*>(event->copy()), button};
}
