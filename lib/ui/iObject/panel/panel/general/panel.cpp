#include "panel.hpp"
#include "../interaction/hide/hidePanelInteraction.hpp"
#include "../interaction/move/dont/dontMovePanelInteraction.hpp"

namespace ui {
	Panel::Panel(
		BoxPtr<IScalable>&& object,
		BoxPtr<HidePanelInteraction> hideInteraction,
		BoxPtr<MovePanelInteraction> moveInteraction,
		BoxPtr<ISizing2> sizing,
		BoxPtr<IPositioning2> positioning,
		bool displayed
	) : BasePanel(std::forward<BoxPtr<IScalable> >(object), sizing, positioning, displayed),
		hideInteraction(hideInteraction), moveInteraction(moveInteraction), interactionManager(nullptr) {
	}
	
	Panel::Panel(
		BoxPtr<IScalable>&& object,
		BoxPtr<HidePanelInteraction> hideInteraction,
		BoxPtr<ISizing2> sizing,
		BoxPtr<IPositioning2> positioning,
		bool displayed
	) : BasePanel(std::forward<BoxPtr<IScalable> >(object), sizing, positioning, displayed),
		hideInteraction(hideInteraction), moveInteraction(new DontMovePanelInteraction{}), interactionManager(nullptr) {
	}
	
	Panel::Panel(const Panel& other) :
		BasePanel(other), hideInteraction(other.hideInteraction), moveInteraction(other.moveInteraction), interactionManager(other.interactionManager) {
		hideInteraction->setPanel(*this);
	}
	
	void Panel::init(InitInfo initInfo) {
		BasePanel::init(initInfo);
		InitInfo newInitInfo{initInfo.window, initInfo.renderTarget, this->drawManager, this->updateManager, initInfo.interactionManager, initInfo.interactionStack, this->panelManager};
		object->init(newInitInfo);
		hideInteraction->init({initInfo, *this});
		moveInteraction->init({initInfo, *this});
		this->interactionManager = &initInfo.interactionManager;
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
	
	Panel* Panel::copy() {
		return new Panel{*this};
	}
	
	bool DecodePointer<Panel>::decodePointer(const YAML::Node& node, Panel*& panel) {
		panel = new Panel{
			node["object"].as<BoxPtr<IScalable> >(),
			node["hide-interaction"].as<BoxPtr<HidePanelInteraction> >(),
			BoxPtr{convDefPtr<MovePanelInteraction, DontMovePanelInteraction>(node["move-interaction"])},
			node["sizing"].as<BoxPtr<ISizing2> >(),
			node["positioning"].as<BoxPtr<IPositioning2> >(),
			convDef(node["displayed"], false)
		};
		return true;
	}
}
