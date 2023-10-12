#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace ie {
	class Window;
	
	class DrawManager;
	
	class UpdateManager;
	
	class InteractionManager;
	
	class InteractionStack;
	
	class IPanelManager;
	
	struct InitInfo {
		sf::RenderWindow& window;
		sf::RenderTarget& renderTarget;
		DrawManager& drawManager;
		UpdateManager& updateManager;
		InteractionManager& interactionManager;
		InteractionStack& interactionStack;
		IPanelManager& panelManager;
		
		InitInfo(sf::RenderWindow& window_, sf::RenderTarget& renderTarget_, DrawManager& drawManager_, UpdateManager& updateManager_, InteractionManager& interactionManager_, InteractionStack& interactionStack_, IPanelManager& panelManager_);
		
		InitInfo copy(sf::RenderWindow& window_) const;
		
		InitInfo copy(sf::RenderTarget& renderTarget_) const;
		
		InitInfo copy(DrawManager& drawManager_) const;
		
		InitInfo copy(UpdateManager& updateManager_) const;
		
		InitInfo copy(InteractionManager& interactionManager_) const;
		
		InitInfo copy(InteractionStack& interactionStack_) const;
		
		InitInfo copy(IPanelManager& panelManager_) const;
	};
}
