#include "PanelManagerInterceptor.hpp"

namespace ui {
	PanelManagerInterceptor::PanelManagerInterceptor(IPanelManager& panelManager) : panelManager(&panelManager) {
	}
	
	PanelManagerInterceptor::PanelManagerInterceptor() : panelManager(nullptr) {
	}
	
	void PanelManagerInterceptor::init(IPanelManager& panelManager) {
		this->panelManager = &panelManager;
	}
	
	void PanelManagerInterceptor::clear() {
		for(const auto& panel: panels) {
			panelManager->removePanel(panel);
		}
		
		panels.clear();
	}
	
	bool PanelManagerInterceptor::isFree() {
		return panelManager->isFree();
	}
	
	bool PanelManagerInterceptor::inConstPanels(sf::Vector2f pointPosition) {
		return panelManager->inConstPanels(pointPosition);
	}
	
	void PanelManagerInterceptor::addPanel(BasePanel* panel) {
		panelManager->addPanel(panel);
		panels.push_back(panel);
	}
	
	void PanelManagerInterceptor::removePanel(BasePanel* panel) {
		panelManager->removePanel(panel);
	}
	
	void PanelManagerInterceptor::displayPanel(BasePanel* panel) {
		panelManager->displayPanel(panel);
	}
	
	void PanelManagerInterceptor::hidePanel(BasePanel* panel) {
		panelManager->hidePanel(panel);
	}
	
	void PanelManagerInterceptor::draw() {
		panelManager->draw();
	}
	
	void PanelManagerInterceptor::update() {
		panelManager->update();
	}
	
	bool PanelManagerInterceptor::updateInteractions(sf::Vector2f mousePosition, bool active) {
		return panelManager->updateInteractions(mousePosition, active);
	}
	}