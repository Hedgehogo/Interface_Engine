#include "PanelManagerInterceptor.hpp"

namespace ie {
	PanelManagerInterceptor::PanelManagerInterceptor(IPanelManager& panel_manager) : panel_manager_(&panel_manager) {
	}
	
	auto PanelManagerInterceptor::clear() -> void {
		for(auto const& panel: panels_) {
			panel_manager_->remove_panel(panel);
		}
		
		panels_.clear();
	}
	
	auto PanelManagerInterceptor::is_free() -> bool {
		return panel_manager_->is_free();
	}
	
	auto PanelManagerInterceptor::in_const_panels(sf::Vector2f point_position) -> bool {
		return panel_manager_->in_const_panels(point_position);
	}
	
	auto PanelManagerInterceptor::add_panel(BasePanel* panel) -> void {
		panel_manager_->add_panel(panel);
		panels_.push_back(panel);
	}
	
	auto PanelManagerInterceptor::remove_panel(BasePanel* panel) -> void {
		panel_manager_->remove_panel(panel);
	}
	
	auto PanelManagerInterceptor::display_panel(BasePanel* panel) -> void {
		panel_manager_->display_panel(panel);
	}
	
	auto PanelManagerInterceptor::hide_panel(BasePanel* panel) -> void {
		panel_manager_->hide_panel(panel);
	}
	
	auto PanelManagerInterceptor::draw() -> void {
		panel_manager_->draw();
	}
	
	auto PanelManagerInterceptor::update() -> void {
		panel_manager_->update();
	}
	
	auto PanelManagerInterceptor::handle_event(Event event, bool active) -> bool {
		return panel_manager_->handle_event(event, active);
	}
}