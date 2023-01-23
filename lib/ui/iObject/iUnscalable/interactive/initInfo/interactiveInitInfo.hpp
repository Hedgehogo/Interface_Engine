#pragma once
#include "../../../initInfo/initInfo.hpp"

namespace ui {
	struct InteractiveInitInfo {
		sf::RenderTarget &renderTarget;
		DrawManager &drawManager;
		UpdateManager &updateManager;
		IPanelManager &panelManager;
		
		InteractiveInitInfo(sf::RenderTarget &renderTarget_, DrawManager &drawManager_, UpdateManager &updateManager_, IPanelManager &panelManager_);
		
		InteractiveInitInfo copy(sf::RenderTarget &renderTarget_) const;
		
		InteractiveInitInfo copy(DrawManager &drawManager_) const;
		
		InteractiveInitInfo copy(UpdateManager &updateManager_) const;
		
		InteractiveInitInfo copy(IPanelManager &panelManager_) const;
		
		InitInfo toGeneral(InteractionManager &interactionManager_, InteractionStack &interactionStack_) const;
	};
}
