#include "clickPanelInteraction.hpp"

ui::ClickPanelInteraction::ClickPanelInteraction(ui::PanelEvent *event, sf::Mouse::Button button) : OneButtonInteraction(event, button), BasePanelInteraction() {}

void ui::ClickPanelInteraction::init(ui::Panel &panel, ui::PanelManager &panelManager) {
	dynamic_cast<ui::PanelEvent*>(event)->init(panel, panelManager);
}

void ui::ClickPanelInteraction::setPanel(ui::Panel &panel) {
	dynamic_cast<ui::PanelEvent*>(event)->setPanel(panel);
}