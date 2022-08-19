#include "constPanel.hpp"
#include "../../manager/panelManager.h"
#include "../../../../drawable/manager/drawManager.h"

namespace ui {
	ConstPanel::ConstPanel(IScalable *object, BaseSizing2 *sizing, BasePositioning2 *positioning, bool displayed) :
		BasePanel(object, sizing, positioning, displayed) {}
	
	void ConstPanel::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) {
		BasePanel::init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
		object->init(renderTarget, this->drawManager, this->updateManager, interactionManager, interactionStack, panelManager);
		panelManager.displayPanel(this);
	}
	
	bool ConstPanel::isIndependent() { return false; }
	
	bool ConstPanel::isFree() { return true; }
	
	ConstPanel *ConstPanel::copy() {
		ConstPanel* constPanel {new ConstPanel(object->copy(), sizing->copy(), positioning->copy(), displayed)};
		BasePanel::copy(constPanel);
		return constPanel;
	}
	
	ConstPanel *ConstPanel::createFromYaml(const YAML::Node &node) {
		IScalable *object;
		BaseSizing2 *sizing;
		BasePositioning2 *positioning;
		bool displayed{false};
		
		node["object"] >> object;
		node["sizing"] >> sizing;
		node["positioning"] >> positioning;
		if(node["displayed"])
			node["displayed"] >> displayed;
		
		return new ConstPanel{object, sizing, positioning, displayed};
	}
}