#include "panelManager.h"
#include <utility>
#include <iostream>

namespace ui {
	PanelManager::PanelManager(std::vector<Panel *> panels) : panels(std::move(panels)), activePanels() {}
	
	void PanelManager::addPanel(Panel *panel) {
		panels.push_back(panel);
	}
	
	void PanelManager::displayPanel(Panel *panel) {
		activePanels.push_back(panel);
	}
	
	void PanelManager::hidePanel(Panel *panel) {
		for(unsigned i = 0; i < activePanels.size(); ++i) {
			if(activePanels[i] == panel) {
				activePanels.erase(activePanels.cbegin() + i);
				break;
			}
		}
	}
	
	void PanelManager::update() {
		for(int i = panels.size() - 1; i >= 0; --i) {
			panels[i]->update();
		}
	}
	
	void PanelManager::draw() {
		for(const auto &panel: activePanels) {
			panel->draw();
		}
	}
	
	void PanelManager::updateInteractions(sf::Vector2f mousePosition) {
		bool active = true;
		for(long long i = static_cast<long long>(activePanels.size()) - 1; i >= 0; --i) {
			active = active && !activePanels[i]->updateInteractions(true, mousePosition);
		}
	}
}
