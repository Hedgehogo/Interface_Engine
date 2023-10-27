#include "PanelManager.hpp"
#include <utility>
#include <iostream>

namespace ie {
	PanelManager::PanelManager(std::vector<BasePanel*> panels) : panels_(std::move(panels)), active_panels_() {
	}
	
	size_t PanelManager::size() {
		return panels_.size();
	}
	
	BasePanel& PanelManager::get(size_t index) {
		return *panels_.at(index);
	}
	
	void PanelManager::print() {
		for(const auto& panel: panels_) {
			std::cout << panel << ", ";
		}
		if(!panels_.empty()) {
			std::cout << std::endl;
		}
	}
	
	void PanelManager::print_active() {
		for(const auto& panel: active_panels_) {
			std::cout << panel << ", ";
		}
		if(!active_panels_.empty()) {
			std::cout << std::endl;
		}
	}
	
	bool PanelManager::is_free() {
		return std::all_of(active_panels_.begin(), active_panels_.end(), [](BasePanel* panel) {
			return !panel->is_independent();
		});
	}
	
	bool PanelManager::in_const_panels(sf::Vector2f point_position) {
		return std::any_of(active_panels_.begin(), active_panels_.end(), [&point_position](BasePanel* panel) {
			return !panel->is_independent() && panel->in_panel(point_position);
		});
	}
	
	void PanelManager::add_panel(BasePanel* panel) {
		panels_.insert(panels_.begin(), panel);
	}
	
	void PanelManager::remove_panel(BasePanel* panel) {
		if(auto elem = std::find(panels_.begin(), panels_.end(), panel); elem != panels_.end())
			panels_.erase(elem);
	}
	
	void PanelManager::display_panel(BasePanel* panel) {
		if(std::find(active_panels_.begin(), active_panels_.end(), panel) == active_panels_.end())
			active_panels_.insert(active_panels_.begin(), panel);
	}
	
	void PanelManager::hide_panel(BasePanel* panel) {
		if(auto iterator = std::find(active_panels_.begin(), active_panels_.end(), panel); iterator != active_panels_.end())
			active_panels_.erase(iterator);
	}
	
	void PanelManager::draw() {
		for(auto panel = active_panels_.rbegin(); panel != active_panels_.rend(); ++panel) {
			(*panel)->draw();
		}
	}
	
	void PanelManager::update() {
		for(auto& panel: panels_) {
			panel->update();
		}
	}
	
	bool PanelManager::update_interactions(sf::Vector2f mouse_position, bool active) {
		for(auto iterator = active_panels_.begin(); iterator != active_panels_.end(); ++iterator) {
			if((*iterator)->update_interactions(mouse_position, active) && active) {
				BasePanel* panel = *iterator;
				active_panels_.erase(iterator);
				active_panels_.insert(active_panels_.begin(), panel);
				active = false;
			}
		}
		return !active;
	}
}
