#include "panelInteractionInitInfo.hpp"

namespace ui {
	PanelInteractionInitInfo::PanelInteractionInitInfo(Window& window_, sf::RenderTarget& renderTarget_, InteractionManager& interactionManager_, InteractionStack& interactionStack_, IPanelManager& panelManager_, Panel& panel_) :
		window(window_), renderTarget(renderTarget_), interactionManager(interactionManager_), interactionStack(interactionStack_), panelManager(panelManager_), panel(panel_) {
	}
	
	PanelInteractionInitInfo::PanelInteractionInitInfo(InteractionInitInfo interactionInitInfo, Panel& panel_) :
	PanelInteractionInitInfo(interactionInitInfo.window, interactionInitInfo.renderTarget, interactionInitInfo.interactionManager, interactionInitInfo.interactionStack, interactionInitInfo.panelManager, panel_){
	}
	
	PanelInteractionInitInfo::PanelInteractionInitInfo(InitInfo initInfo, Panel& panel_) :
		PanelInteractionInitInfo(initInfo.window, initInfo.renderTarget, initInfo.interactionManager, initInfo.interactionStack, initInfo.panelManager, panel_){
	}
	
	InteractionInitInfo PanelInteractionInitInfo::toGeneral() {
		return {window, renderTarget, interactionManager, interactionStack, panelManager};
	}
	
	PanelInteractionInitInfo PanelInteractionInitInfo::copy(Window& window_) const {
		return {window_, renderTarget, interactionManager, interactionStack, panelManager, panel};
	}
	
	PanelInteractionInitInfo PanelInteractionInitInfo::copy(sf::RenderTarget& renderTarget_) const {
		return {window, renderTarget_, interactionManager, interactionStack, panelManager, panel};
	}
	
	PanelInteractionInitInfo PanelInteractionInitInfo::copy(InteractionManager& interactionManager_) const {
		return {window, renderTarget, interactionManager_, interactionStack, panelManager, panel};
	}
	
	PanelInteractionInitInfo PanelInteractionInitInfo::copy(InteractionStack& interactionStack_) const {
		return {window, renderTarget, interactionManager, interactionStack_, panelManager, panel};
	}
	
	PanelInteractionInitInfo PanelInteractionInitInfo::copy(IPanelManager& panelManager_) const {
		return {window, renderTarget, interactionManager, interactionStack, panelManager_, panel};
	}
	
	PanelInteractionInitInfo PanelInteractionInitInfo::copy(Panel& panel_) const {
		return {window, renderTarget, interactionManager, interactionStack, panelManager, panel_};
	}
}