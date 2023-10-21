#include "PanelManager.hpp"
#include <utility>
#include <iostream>

namespace ie {
	PanelManager::PanelManager(std::vector<BasePanel*> panels) : panels(std::move(panels)), active_panels() {
	}
	
	size_t PanelManager::size() {
		return panels.size();
	}
	
	BasePanel& PanelManager::get(size_t index) {
		return *panels.at(index);
	}
	
	void PanelManager::print() {
		for(const auto& panel: panels) {
			std::cout << panel << ", ";
		}
		if(!panels.empty()) {
			std::cout << std::endl;
		}
	}
	
	void PanelManager::print_active() {
		for(const auto& panel: active_panels) {
			std::cout << panel << ", ";
		}
		if(!active_panels.empty()) {
			std::cout << std::endl;
		}
	}
	
	bool PanelManager::is_free() {
		return std::all_of(active_panels.begin(), active_panels.end(), [](BasePanel* panel) {
			return !panel->is_independent();
		});
	}
	
	bool PanelManager::in_const_panels(sf::Vector2f point_position) {
		return std::any_of(active_panels.begin(), active_panels.end(), [&point_position](BasePanel* panel) {
			return !panel->is_independent() && panel->in_panel(point_position);
		});
	}
	
	void PanelManager::add_panel(BasePanel* panel) {
		panels.insert(panels.begin(), panel);
	}
	
	void PanelManager::remove_panel(BasePanel* panel) {
		if(auto elem = std::find(panels.begin(), panels.end(), panel); elem != panels.end())
			panels.erase(elem);
	}
	
	void PanelManager::display_panel(BasePanel* panel) {
		if(std::find(active_panels.begin(), active_panels.end(), panel) == active_panels.end())
			active_panels.insert(active_panels.begin(), panel);
	}
	
	void PanelManager::hide_panel(BasePanel* panel) {
		if(auto iterator = std::find(active_panels.begin(), active_panels.end(), panel); iterator != active_panels.end())
			active_panels.erase(iterator);
	}
	
	void PanelManager::draw() {
		for(auto panel = active_panels.rbegin(); panel != active_panels.rend(); ++panel) {
			(*panel)->draw();
		}
	}
	
	void PanelManager::update() {
		for(auto& panel: panels) {
			panel->update();
		}
	}
	
	bool PanelManager::update_interactions(sf::Vector2f mouse_position, bool active) {
		for(auto iterator = active_panels.begin(); iterator != active_panels.end(); ++iterator) {
			if((*iterator)->update_interactions(mouse_position, active) && active) {
				BasePanel* panel = *iterator;
				active_panels.erase(iterator);
				active_panels.insert(active_panels.begin(), panel);
				active = false;
			}
		}
		return !active;
	}
}
