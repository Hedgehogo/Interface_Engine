#pragma once

#include "../../../initInfo/initInfo.hpp"

namespace ui {
	struct InteractiveInitInfo {
		Window& window;
		sf::RenderTarget& renderTarget;
		DrawManager& drawManager;
		UpdateManager& updateManager;
		IPanelManager& panelManager;
		
		InteractiveInitInfo(Window& window_, sf::RenderTarget& renderTarget_, DrawManager& drawManager_, UpdateManager& updateManager_, IPanelManager& panelManager_);
		
		InteractiveInitInfo copy(Window& window_) const;
		
		InteractiveInitInfo copy(sf::RenderTarget& renderTarget_) const;
		
		InteractiveInitInfo copy(DrawManager& drawManager_) const;
		
		InteractiveInitInfo copy(UpdateManager& updateManager_) const;
		
		InteractiveInitInfo copy(IPanelManager& panelManager_) const;
		
		InitInfo toGeneral(InteractionManager& interactionManager_, InteractionStack& interactionStack_) const;
	};
}
