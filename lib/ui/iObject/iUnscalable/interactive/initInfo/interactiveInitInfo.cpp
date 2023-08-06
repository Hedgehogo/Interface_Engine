#include "interactiveInitInfo.hpp"

namespace ui {
	InteractiveInitInfo::InteractiveInitInfo(sf::RenderWindow& window_, sf::RenderTarget& renderTarget_, DrawManager& drawManager_, UpdateManager& updateManager_, IPanelManager& panelManager_) :
		window(window_), renderTarget(renderTarget_), drawManager(drawManager_), updateManager(updateManager_), panelManager(panelManager_) {
	}
	
	InteractiveInitInfo InteractiveInitInfo::copy(sf::RenderWindow& window_) const {
		return InteractiveInitInfo(window_, renderTarget, drawManager, updateManager, panelManager);
	}
	
	InteractiveInitInfo InteractiveInitInfo::copy(sf::RenderTarget& renderTarget_) const {
		return InteractiveInitInfo(window, renderTarget_, drawManager, updateManager, panelManager);
	}
	
	InteractiveInitInfo InteractiveInitInfo::copy(DrawManager& drawManager_) const {
		return InteractiveInitInfo(window, renderTarget, drawManager_, updateManager, panelManager);
	}
	
	InteractiveInitInfo InteractiveInitInfo::copy(UpdateManager& updateManager_) const {
		return InteractiveInitInfo(window, renderTarget, drawManager, updateManager_, panelManager);
	}
	
	InteractiveInitInfo InteractiveInitInfo::copy(IPanelManager& panelManager_) const {
		return InteractiveInitInfo(window, renderTarget, drawManager, updateManager, panelManager_);
	}
	
	InitInfo InteractiveInitInfo::toGeneral(InteractionManager& interactionManager_, InteractionStack& interactionStack_) const {
		return InitInfo(window, renderTarget, drawManager, updateManager, interactionManager_, interactionStack_, panelManager);
	}
}