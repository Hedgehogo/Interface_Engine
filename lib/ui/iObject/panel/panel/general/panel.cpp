#include "panel.hpp"
#include "../interaction/hide/hidePanelInteraction.hpp"
#include "../interaction/move/dont/dontMovePanelInteraction.hpp"

namespace ui {
	Panel::Panel(IScalable *object, HidePanelInteraction *hideInteraction, MovePanelInteraction *moveInteraction, ISizing2 *sizing, IPositioning2 *positioning, bool displayed) :
		BasePanel(object, sizing, positioning, displayed), hideInteraction(hideInteraction), moveInteraction(moveInteraction), interactionManager(nullptr) {
	}
	
	Panel::Panel(IScalable *object, HidePanelInteraction *hideInteraction, ISizing2 *sizing, IPositioning2 *positioning, bool displayed) :
		Panel(object, hideInteraction, new DontMovePanelInteraction{}, sizing, positioning, displayed) {
	}
	
	void Panel::init(InitInfo initInfo) {
		BasePanel::init(initInfo);
		InitInfo newInitInfo{initInfo.renderTarget, this->drawManager, this->updateManager, initInfo.interactionManager, initInfo.interactionStack, this->panelManager};
		object->init(newInitInfo);
		hideInteraction->init(*this, initInfo.panelManager);
		moveInteraction->init(*this, initInfo.panelManager);
		this->interactionManager = &initInfo.interactionManager;
	}
	
	Panel::~Panel() {
		delete hideInteraction;
	}
	
	void Panel::setDisplayed() {
		displayed = true;
	}
	
	bool Panel::isIndependent() {
		return true;
	}
	
	bool Panel::isFree() {
		return panelManager.isFree();
	}
	
	bool Panel::inConstPanels(sf::Vector2f pointPosition) {
		return panelManager.inConstPanels(pointPosition);
	}
	
	void Panel::draw() {
		BasePanel::draw();
		panelManager.draw();
	}
	
	void Panel::update() {
		panelManager.update();
		if(oldDisplayed != displayed) {
			if(displayed) {
				interactionManager->addInteraction(*hideInteraction);
				interactionManager->addInteraction(*moveInteraction);
			} else {
				interactionManager->deleteInteraction(*hideInteraction);
				interactionManager->deleteInteraction(*moveInteraction);
			}
		}
		BasePanel::update();
	}
	
	bool Panel::updateInteractions(sf::Vector2f mousePosition, bool active) {
		displayed = true;
		this->active = active;
		if(panelManager.updateInteractions(mousePosition, active))
			return true;
		return BasePanel::updateInteractions(mousePosition);
	}
	
	void Panel::copy(Panel *panel) {
		BasePanel::copy(panel);
		panel->interactionManager = this->interactionManager;
	}
	
	Panel *Panel::copy() {
		Panel *panel{new Panel(object->copy(), hideInteraction->copy(), moveInteraction->copy(), sizing->copy(), positioning->copy(), displayed)};
		panel->hideInteraction->setPanel(*panel);
		Panel::copy(panel);
		return panel;
	}
	
	bool convertPointer(const YAML::Node &node, Panel *&panel) {
		IScalable *object;
		HidePanelInteraction *hideInteraction;
		ISizing2 *sizing;
		IPositioning2 *positioning;
		bool displayed{false};
		
		node["object"] >> object;
		node["hide-interaction"] >> hideInteraction;
		node["sizing"] >> sizing;
		node["positioning"] >> positioning;
		if(node["displayed"])
			node["displayed"] >> displayed;
		
		if(node["move-interaction"]) {
			MovePanelInteraction *moveInteraction;
			
			node["move-interaction"] >> moveInteraction;
			
			{ panel = new Panel{object, hideInteraction, moveInteraction, sizing, positioning, displayed}; return true; }
		} else {
			{ panel = new Panel{object, hideInteraction, sizing, positioning, displayed}; return true; }
		}
	}
}
