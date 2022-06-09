#include "panelStack.h"
#include <utility>
#include <iostream>

namespace ui {
	PanelStack::PanelStack(std::vector<Panel *> panels) : panels(std::move(panels)) {}
	
	void PanelStack::displayPanel(Panel *panel) {
		panels.push_back(panel);
	}
	
	void PanelStack::hidePanel(Panel *panel) {
		for(unsigned i = 0; i < panels.size(); ++i) {
			if(panels[i] == panel) {
				panels.erase(panels.cbegin() + i);
				break;
			}
		}
	}
	
	void PanelStack::update() {
		for(int i = panels.size() - 1; i >= 0; --i) {
			panels[i]->update();
		}
	}
	
	void PanelStack::draw() {
		for(const auto &panel: panels) {
			panel->draw();
		}
	}
	
	void PanelStack::updateInteractions(sf::Vector2f mousePosition) {
		bool active = true;
		for(int i = panels.size() - 1; i >= 0; --i) {
			if(active) {
				active = !panels[i]->updateInteractions(true, mousePosition);
			} else {
				panels[i]->updateInteractions(false, mousePosition);
			}
		}
		return;
	}
}
