#include "interactiveInitInfo.hpp"

namespace ui {
	InteractiveInitInfo::InteractiveInitInfo(sf::RenderTarget &renderTarget_, DrawManager &drawManager_, UpdateManager &updateManager_, IPanelManager &panelManager_) :
		renderTarget(renderTarget_), drawManager(drawManager_), updateManager(updateManager_), panelManager(panelManager_) {
		
	}
	
	InteractiveInitInfo InteractiveInitInfo::copy(sf::RenderTarget &renderTarget_) const {
		return InteractiveInitInfo(renderTarget_, drawManager, updateManager, panelManager);
	}
	
	InteractiveInitInfo InteractiveInitInfo::copy(DrawManager &drawManager_) const {
		return InteractiveInitInfo(renderTarget, drawManager_, updateManager, panelManager);
	}
	
	InteractiveInitInfo InteractiveInitInfo::copy(UpdateManager &updateManager_) const {
		return InteractiveInitInfo(renderTarget, drawManager, updateManager_, panelManager);
	}
	
	InteractiveInitInfo InteractiveInitInfo::copy(IPanelManager &panelManager_) const {
		return InteractiveInitInfo(renderTarget, drawManager, updateManager, panelManager_);
	}
	
	InitInfo InteractiveInitInfo::toGeneral(InteractionManager &interactionManager_, InteractionStack &interactionStack_) const {
		return InitInfo(renderTarget, drawManager, updateManager, interactionManager_, interactionStack_, panelManager);
	}
}