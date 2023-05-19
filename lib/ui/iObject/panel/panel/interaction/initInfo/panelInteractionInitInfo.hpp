#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "ui/interaction/initInfo/interactionInitInfo.hpp"

namespace ui {
	class Panel;
	
	struct PanelInteractionInitInfo {
		Window& window;
		sf::RenderTarget& renderTarget;
		InteractionManager& interactionManager;
		InteractionStack& interactionStack;
		IPanelManager& panelManager;
		Panel& panel;
		
		PanelInteractionInitInfo(Window& window_, sf::RenderTarget& renderTarget_, InteractionManager& interactionManager_, InteractionStack& interactionStack_, IPanelManager& panelManager_, Panel& panel_);
		
		PanelInteractionInitInfo(InteractionInitInfo interactionInitInfo, Panel& panel_);
		
		PanelInteractionInitInfo(InitInfo initInfo, Panel& panel_);
		
		InteractionInitInfo toGeneral();
		
		PanelInteractionInitInfo copy(Window& window_) const;
		
		PanelInteractionInitInfo copy(sf::RenderTarget& renderTarget_) const;
		
		PanelInteractionInitInfo copy(InteractionManager& interactionManager_) const;
		
		PanelInteractionInitInfo copy(InteractionStack& interactionStack_) const;
		
		PanelInteractionInitInfo copy(IPanelManager& panelManager_) const;
		
		PanelInteractionInitInfo copy(Panel& panel_) const;
	};
}
