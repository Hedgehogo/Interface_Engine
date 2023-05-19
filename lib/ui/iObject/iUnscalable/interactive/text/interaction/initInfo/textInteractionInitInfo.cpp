#include "textInteractionInitInfo.hpp"

namespace ui {
	TextInteractionInitInfo::TextInteractionInitInfo(Window& window_, sf::RenderTarget& renderTarget_, InteractionManager& interactionManager_, InteractionStack& interactionStack_, IPanelManager& panelManager_, Text& text_) :
		window(window_), renderTarget(renderTarget_), interactionManager(interactionManager_), interactionStack(interactionStack_), panelManager(panelManager_), text(text_) {
	}
	
	TextInteractionInitInfo::TextInteractionInitInfo(InteractionInitInfo interactionInitInfo, Text& text_) :
	TextInteractionInitInfo(interactionInitInfo.window, interactionInitInfo.renderTarget, interactionInitInfo.interactionManager, interactionInitInfo.interactionStack, interactionInitInfo.panelManager, text_){
	}
	
	TextInteractionInitInfo::TextInteractionInitInfo(InitInfo initInfo, Text& text_) :
		TextInteractionInitInfo(initInfo.window, initInfo.renderTarget, initInfo.interactionManager, initInfo.interactionStack, initInfo.panelManager, text_){
	}
	
	InteractionInitInfo TextInteractionInitInfo::toGeneral() {
		return {window, renderTarget, interactionManager, interactionStack, panelManager};
	}
	
	TextInteractionInitInfo TextInteractionInitInfo::copy(Window& window_) const {
		return {window_, renderTarget, interactionManager, interactionStack, panelManager, text};
	}
	
	TextInteractionInitInfo TextInteractionInitInfo::copy(sf::RenderTarget& renderTarget_) const {
		return {window, renderTarget_, interactionManager, interactionStack, panelManager, text};
	}
	
	TextInteractionInitInfo TextInteractionInitInfo::copy(InteractionManager& interactionManager_) const {
		return {window, renderTarget, interactionManager_, interactionStack, panelManager, text};
	}
	
	TextInteractionInitInfo TextInteractionInitInfo::copy(InteractionStack& interactionStack_) const {
		return {window, renderTarget, interactionManager, interactionStack_, panelManager, text};
	}
	
	TextInteractionInitInfo TextInteractionInitInfo::copy(IPanelManager& panelManager_) const {
		return {window, renderTarget, interactionManager, interactionStack, panelManager_, text};
	}
	
	TextInteractionInitInfo TextInteractionInitInfo::copy(Text& text_) const {
		return {window, renderTarget, interactionManager, interactionStack, panelManager, text_};
	}
}