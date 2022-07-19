#include "constPanel.h"
#include "../../panelManager/panelManager.h"

namespace ui {
	ConstPanel::ConstPanel(IScalable *object, Sizing2 *sizing, Positioning2 *positioning, bool displayed) :
		BasePanel(object, sizing, positioning, displayed) {}
	
	void ConstPanel::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		BasePanel::init(renderTarget, interactionStack, interactionManager, panelManager);
		initObject(object, renderTarget, interactionStack, interactionManager, panelManager);
		panelManager.displayPanel(this);
	}
	
	bool ConstPanel::isIndependent() { return false; }
	
	bool ConstPanel::isFree() { return true; }
	
	ConstPanel *ConstPanel::copy() {
		ConstPanel* constPanel {new ConstPanel(object->copy(), sizing->copy(), positioning->copy(), displayed)};
		BasePanel::copy(constPanel);
		return constPanel;
	}
}