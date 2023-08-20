#include "interactionInitInfo.hpp"

namespace ui {
	InteractionInitInfo::InteractionInitInfo(sf::RenderWindow& window_, sf::RenderTarget& renderTarget_, InteractionManager& interactionManager_, InteractionStack& interactionStack_, IPanelManager& panelManager_) :
		window(window_), renderTarget(renderTarget_), interactionManager(interactionManager_), interactionStack(interactionStack_), panelManager(panelManager_) {
	}
	
	InteractionInitInfo::InteractionInitInfo(InitInfo initInfo) :
		InteractionInitInfo(initInfo.window, initInfo.renderTarget, initInfo.interactionManager, initInfo.interactionStack, initInfo.panelManager){
	}
	
	InteractionInitInfo InteractionInitInfo::copy(sf::RenderWindow& window_) const {
		return {window_, renderTarget, interactionManager, interactionStack, panelManager};
	}
	
	InteractionInitInfo InteractionInitInfo::copy(sf::RenderTarget& renderTarget_) const {
		return {window, renderTarget_, interactionManager, interactionStack, panelManager};
	}
	
	InteractionInitInfo InteractionInitInfo::copy(InteractionManager& interactionManager_) const {
		return {window, renderTarget, interactionManager_, interactionStack, panelManager};
	}
	
	InteractionInitInfo InteractionInitInfo::copy(InteractionStack& interactionStack_) const {
		return {window, renderTarget, interactionManager, interactionStack_, panelManager};
	}
	
	InteractionInitInfo InteractionInitInfo::copy(IPanelManager& panelManager_) const {
		return {window, renderTarget, interactionManager, interactionStack, panelManager_};
	}
}