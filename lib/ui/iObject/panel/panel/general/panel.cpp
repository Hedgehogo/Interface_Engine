#include "panel.hpp"
#include "../interaction/hide/hidePanelInteraction.hpp"
#include "../interaction/move/dont/dontMovePanelInteraction.hpp"

ui::Panel::Panel(IScalable *object, HidePanelInteraction *hideInteraction, MovePanelInteraction *moveInteraction, BaseSizing2 *sizing, BasePositioning2 *positioning, bool displayed) :
	BasePanel(object, sizing, positioning, displayed), hideInteraction(hideInteraction), moveInteraction(moveInteraction), interactionManager(nullptr) {}

ui::Panel::Panel(IScalable *object, HidePanelInteraction *hideInteraction, BaseSizing2 *sizing, BasePositioning2 *positioning, bool displayed) :
	Panel(object, hideInteraction, new DontMovePanelInteraction{}, sizing, positioning, displayed) {}

void ui::Panel::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) {
	BasePanel::init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
	object->init(renderTarget, this->drawManager, this->updateManager, interactionManager, interactionStack, this->panelManager);
	hideInteraction->init(*this, panelManager);
	moveInteraction->init(*this, panelManager);
	this->interactionManager = &interactionManager;
}

ui::Panel::~Panel() {
	delete hideInteraction;
}

void ui::Panel::setDisplayed() { displayed = true; }

bool ui::Panel::isIndependent() { return true; }

bool ui::Panel::isFree() { return panelManager.isFree(); }

bool ui::Panel::inConstPanels(sf::Vector2f pointPosition) {
	return panelManager.inConstPanels(pointPosition);
}

void ui::Panel::draw() {
    BasePanel::draw();
	panelManager.draw();
}

void ui::Panel::update() {
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

bool ui::Panel::updateInteractions(sf::Vector2f mousePosition, bool active) {
	displayed = true;
	this->active = active;
	if(panelManager.updateInteractions(mousePosition, active)) return true;
	return BasePanel::updateInteractions(mousePosition);
}

void ui::Panel::copy(ui::Panel *panel) {
	BasePanel::copy(panel);
	panel->interactionManager = this->interactionManager;
}

ui::Panel *ui::Panel::copy() {
	Panel* panel {new Panel(object->copy(), hideInteraction->copy(), moveInteraction->copy(), sizing->copy(), positioning->copy(), displayed)};
	panel->hideInteraction->setPanel(*panel);
	Panel::copy(panel);
	return panel;
}

ui::Panel *ui::Panel::createFromYaml(const YAML::Node &node) {
	IScalable *object;
	HidePanelInteraction *hideInteraction;
	BaseSizing2 *sizing;
	BasePositioning2 *positioning;
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
		
		return new Panel{object, hideInteraction, moveInteraction, sizing, positioning, displayed};
	} else {
		return new Panel{object, hideInteraction, sizing, positioning, displayed};
	}
}
