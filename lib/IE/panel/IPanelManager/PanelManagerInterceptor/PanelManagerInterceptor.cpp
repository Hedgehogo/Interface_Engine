#include "PanelManagerInterceptor.hpp"

namespace ie {
	PanelManagerInterceptor::PanelManagerInterceptor(IPanelManager& panel_manager) : panel_manager_(&panel_manager) {
	}
	
	void PanelManagerInterceptor::clear() {
		for(const auto& panel: panels_) {
			panel_manager_->remove_panel(panel);
		}
		
		panels_.clear();
	}
	
	bool PanelManagerInterceptor::is_free() {
		return panel_manager_->is_free();
	}
	
	bool PanelManagerInterceptor::in_const_panels(sf::Vector2f point_position) {
		return panel_manager_->in_const_panels(point_position);
	}
	
	void PanelManagerInterceptor::add_panel(BasePanel* panel) {
		panel_manager_->add_panel(panel);
		panels_.push_back(panel);
	}
	
	void PanelManagerInterceptor::remove_panel(BasePanel* panel) {
		panel_manager_->remove_panel(panel);
	}
	
	void PanelManagerInterceptor::display_panel(BasePanel* panel) {
		panel_manager_->display_panel(panel);
	}
	
	void PanelManagerInterceptor::hide_panel(BasePanel* panel) {
		panel_manager_->hide_panel(panel);
	}
	
	void PanelManagerInterceptor::draw() {
		panel_manager_->draw();
	}
	
	void PanelManagerInterceptor::update() {
		panel_manager_->update();
	}
	
	bool PanelManagerInterceptor::update_interactions(sf::Vector2f mouse_position, bool active) {
		return panel_manager_->update_interactions(mouse_position, active);
	}
	}