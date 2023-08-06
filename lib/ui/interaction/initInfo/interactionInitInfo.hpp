#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "ui/iObject/initInfo/initInfo.hpp"

namespace ui {
	struct InteractionInitInfo {
		sf::RenderWindow& window;
		sf::RenderTarget& renderTarget;
		InteractionManager& interactionManager;
		InteractionStack& interactionStack;
		IPanelManager& panelManager;
		
		InteractionInitInfo(sf::RenderWindow& window_, sf::RenderTarget& renderTarget_, InteractionManager& interactionManager_, InteractionStack& interactionStack_, IPanelManager& panelManager_);
		
		InteractionInitInfo(InitInfo initInfo);
		
		InteractionInitInfo copy(sf::RenderWindow& window_) const;
		
		InteractionInitInfo copy(sf::RenderTarget& renderTarget_) const;
		
		InteractionInitInfo copy(InteractionManager& interactionManager_) const;
		
		InteractionInitInfo copy(InteractionStack& interactionStack_) const;
		
		InteractionInitInfo copy(IPanelManager& panelManager_) const;
	};
}
