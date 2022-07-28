#include "constPanel.h"
#include "../../manager/panelManager.h"
#include "../../../../drawable/manager/drawManager.h"

namespace ui {
	ConstPanel::ConstPanel(IScalable *object, Sizing2 *sizing, Positioning2 *positioning, bool displayed) :
		BasePanel(object, sizing, positioning, displayed) {}
	
	void ConstPanel::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) {
		BasePanel::init(renderTarget, drawManager, interactionManager, interactionStack, panelManager);
		object->init(renderTarget, drawManager, interactionManager, interactionStack, panelManager);
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