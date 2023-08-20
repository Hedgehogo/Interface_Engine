#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "IE/Interaction/InteractionInitInfo/InteractionInitInfo.hpp"

namespace ui {
	class Panel;
	
	struct PanelInteractionInitInfo {
		sf::RenderWindow& window;
		sf::RenderTarget& renderTarget;
		InteractionManager& interactionManager;
		InteractionStack& interactionStack;
		IPanelManager& panelManager;
		Panel& panel;
		
		PanelInteractionInitInfo(sf::RenderWindow& window_, sf::RenderTarget& renderTarget_, InteractionManager& interactionManager_, InteractionStack& interactionStack_, IPanelManager& panelManager_, Panel& panel_);
		
		PanelInteractionInitInfo(InteractionInitInfo interactionInitInfo, Panel& panel_);
		
		PanelInteractionInitInfo(InitInfo initInfo, Panel& panel_);
		
		InteractionInitInfo toGeneral();
		
		PanelInteractionInitInfo copy(sf::RenderWindow& window_) const;
		
		PanelInteractionInitInfo copy(sf::RenderTarget& renderTarget_) const;
		
		PanelInteractionInitInfo copy(InteractionManager& interactionManager_) const;
		
		PanelInteractionInitInfo copy(InteractionStack& interactionStack_) const;
		
		PanelInteractionInitInfo copy(IPanelManager& panelManager_) const;
		
		PanelInteractionInitInfo copy(Panel& panel_) const;
	};
}
