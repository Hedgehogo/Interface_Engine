#include "panelManager.hpp"
#include <utility>

namespace ui {
	PanelManager::PanelManager(std::vector<BasePanel *> panels) : panels(std::move(panels)), activePanels() {}
	
	void PanelManager::print() {
		for(const auto &panel: panels) {
			std::cout << panel << ", ";
		}
		if(!panels.empty()) {
			std::cout << std::endl;
		}
	}
	
	void PanelManager::printActive() {
		for(const auto &panel: activePanels) {
			std::cout << panel << ", ";
		}
		if(!activePanels.empty()) {
			std::cout << std::endl;
		}
	}
	
	bool PanelManager::isFree() {
		return std::all_of(activePanels.begin(), activePanels.end(), [](BasePanel* panel) {
			return !panel->isIndependent();
		});
	}
	
	bool PanelManager::inConstPanels(sf::Vector2f pointPosition) {
		return std::any_of(activePanels.begin(), activePanels.end(), [&pointPosition](BasePanel* panel) {
			return !panel->isIndependent() && panel->inPanel(pointPosition);
		});
	}
	
	void PanelManager::addPanel(BasePanel *panel) {
		panels.insert(panels.begin(), panel);
	}
	
	void PanelManager::displayPanel(BasePanel *panel) {
		if(std::find(activePanels.begin(), activePanels.end(), panel) == activePanels.end())
			activePanels.insert(activePanels.begin(), panel);
	}
	
	void PanelManager::hidePanel(BasePanel *panel) {
		if(auto iterator = std::find(activePanels.begin(), activePanels.end(), panel); iterator != activePanels.end())
			activePanels.erase(iterator);
	}
	
	void PanelManager::draw() {
		for(auto panel = activePanels.rbegin(); panel != activePanels.rend(); ++panel) {
			(*panel)->draw();
		}
	}
	
	void PanelManager::update() {
		for(auto &panel: panels) {
			panel->update();
		}
	}
	
	bool PanelManager::updateInteractions(sf::Vector2f mousePosition, bool active) {
		for(auto iterator= activePanels.begin(); iterator != activePanels.end(); ++iterator) {
			if((*iterator)->updateInteractions(mousePosition, active) && active) {
				BasePanel *panel = *iterator;
				activePanels.erase(iterator);
				activePanels.insert(activePanels.begin(), panel);
				active = false;
			}
		}
		return !active;
	}
}
