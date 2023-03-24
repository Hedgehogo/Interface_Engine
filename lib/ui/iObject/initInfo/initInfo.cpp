#include "initInfo.hpp"

namespace ui {
	InitInfo::InitInfo(sf::RenderTarget &renderTarget_, DrawManager &drawManager_, UpdateManager &updateManager_, InteractionManager &interactionManager_, InteractionStack &interactionStack_, IPanelManager &panelManager_) :
		renderTarget(renderTarget_), drawManager(drawManager_), updateManager(updateManager_), interactionManager(interactionManager_), interactionStack(interactionStack_), panelManager(panelManager_) {}
	
	InitInfo InitInfo::copy(sf::RenderTarget &renderTarget_) const {
		return InitInfo(renderTarget_, drawManager, updateManager, interactionManager, interactionStack, panelManager);
	}
	
	InitInfo InitInfo::copy(DrawManager &drawManager_) const {
		return InitInfo(renderTarget, drawManager_, updateManager, interactionManager, interactionStack, panelManager);
	}
	
	InitInfo InitInfo::copy(UpdateManager &updateManager_) const {
		return InitInfo(renderTarget, drawManager, updateManager_, interactionManager, interactionStack, panelManager);
	}
	
	InitInfo InitInfo::copy(InteractionManager &interactionManager_) const {
		return InitInfo(renderTarget, drawManager, updateManager, interactionManager_, interactionStack, panelManager);
	}
	
	InitInfo InitInfo::copy(InteractionStack &interactionStack_) const {
		return InitInfo(renderTarget, drawManager, updateManager, interactionManager, interactionStack_, panelManager);
	}
	
	InitInfo InitInfo::copy(IPanelManager &panelManager_) const {
		return InitInfo(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager_);
	}
}