#include "PanelManager.hpp"
#include <utility>
#include <iostream>

namespace ie {
	PanelManager::PanelManager(std::vector<BasePanel*> panels) : panels_(std::move(panels)), active_panels_() {
	}
	
	auto PanelManager::size() -> size_t {
		return panels_.size();
	}
	
	auto PanelManager::get(size_t index) -> BasePanel& {
		return *panels_.at(index);
	}
	
	auto PanelManager::print() -> void {
		for(const auto& panel: panels_) {
			std::cout << panel << ", ";
		}
		if(!panels_.empty()) {
			std::cout << std::endl;
		}
	}
	
	auto PanelManager::print_active() -> void {
		for(const auto& panel: active_panels_) {
			std::cout << panel << ", ";
		}
		if(!active_panels_.empty()) {
			std::cout << std::endl;
		}
	}
	
	auto PanelManager::is_free() -> bool {
		return std::all_of(active_panels_.begin(), active_panels_.end(), [](BasePanel* panel) {
			return !panel->is_independent();
		});
	}
	
	auto PanelManager::in_const_panels(sf::Vector2f point_position) -> bool {
		return std::any_of(active_panels_.begin(), active_panels_.end(), [&point_position](BasePanel* panel) {
			return !panel->is_independent() && panel->in_panel(point_position);
		});
	}
	
	auto PanelManager::add_panel(BasePanel* panel) -> void {
		panels_.insert(panels_.begin(), panel);
	}
	
	auto PanelManager::remove_panel(BasePanel* panel) -> void {
		if(auto elem = std::find(panels_.begin(), panels_.end(), panel); elem != panels_.end())
			panels_.erase(elem);
	}
	
	auto PanelManager::display_panel(BasePanel* panel) -> void {
		if(std::find(active_panels_.begin(), active_panels_.end(), panel) == active_panels_.end())
			active_panels_.insert(active_panels_.begin(), panel);
	}
	
	auto PanelManager::hide_panel(BasePanel* panel) -> void {
		if(auto iterator = std::find(active_panels_.begin(), active_panels_.end(), panel); iterator != active_panels_.end())
			active_panels_.erase(iterator);
	}
	
	auto PanelManager::draw() -> void {
		for(auto panel = active_panels_.rbegin(); panel != active_panels_.rend(); ++panel) {
			(*panel)->draw();
		}
	}
	
	auto PanelManager::update() -> void {
		for(auto& panel: panels_) {
			panel->update();
		}
	}
	
	auto PanelManager::handle_event(Event event, bool active) -> bool {
		for(auto iterator = active_panels_.begin(); iterator != active_panels_.end(); ++iterator) {
			if((*iterator)->handle_event(event, active) && active) {
				BasePanel* panel = *iterator;
				active_panels_.erase(iterator);
				active_panels_.insert(active_panels_.begin(), panel);
				active = false;
			}
		}
		return !active;
	}
}
