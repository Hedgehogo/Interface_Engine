#include "PanelManagerInterceptor.hpp"

namespace ie {
	PanelManagerInterceptor::PanelManagerInterceptor(IPanelManager& panel_manager) : panel_manager(&panel_manager) {
	}
	
	PanelManagerInterceptor::PanelManagerInterceptor() : panel_manager(nullptr) {
	}
	
	void PanelManagerInterceptor::init(IPanelManager& panel_manager) {
		this->panel_manager = &panel_manager;
	}
	
	void PanelManagerInterceptor::clear() {
		for(const auto& panel: panels) {
			panel_manager->remove_panel(panel);
		}
		
		panels.clear();
	}
	
	bool PanelManagerInterceptor::is_free() {
		return panel_manager->is_free();
	}
	
	bool PanelManagerInterceptor::in_const_panels(sf::Vector2f point_position) {
		return panel_manager->in_const_panels(point_position);
	}
	
	void PanelManagerInterceptor::add_panel(BasePanel* panel) {
		panel_manager->add_panel(panel);
		panels.push_back(panel);
	}
	
	void PanelManagerInterceptor::remove_panel(BasePanel* panel) {
		panel_manager->remove_panel(panel);
	}
	
	void PanelManagerInterceptor::display_panel(BasePanel* panel) {
		panel_manager->display_panel(panel);
	}
	
	void PanelManagerInterceptor::hide_panel(BasePanel* panel) {
		panel_manager->hide_panel(panel);
	}
	
	void PanelManagerInterceptor::draw() {
		panel_manager->draw();
	}
	
	void PanelManagerInterceptor::update() {
		panel_manager->update();
	}
	
	bool PanelManagerInterceptor::update_interactions(sf::Vector2f mouse_position, bool active) {
		return panel_manager->update_interactions(mouse_position, active);
	}
	}