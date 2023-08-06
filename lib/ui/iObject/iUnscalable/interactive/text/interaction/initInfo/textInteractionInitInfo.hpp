#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "ui/interaction/initInfo/interactionInitInfo.hpp"

namespace ui {
	class Text;
	
	struct TextInteractionInitInfo {
		sf::RenderWindow& window;
		sf::RenderTarget& renderTarget;
		InteractionManager& interactionManager;
		InteractionStack& interactionStack;
		IPanelManager& panelManager;
		Text& text;
		
		TextInteractionInitInfo(sf::RenderWindow& window_, sf::RenderTarget& renderTarget_, InteractionManager& interactionManager_, InteractionStack& interactionStack_, IPanelManager& panelManager_, Text& text_);
		
		TextInteractionInitInfo(InteractionInitInfo interactionInitInfo, Text& text_);
		
		TextInteractionInitInfo(InitInfo initInfo, Text& text_);
		
		InteractionInitInfo toGeneral();
		
		TextInteractionInitInfo copy(sf::RenderWindow& window_) const;
		
		TextInteractionInitInfo copy(sf::RenderTarget& renderTarget_) const;
		
		TextInteractionInitInfo copy(InteractionManager& interactionManager_) const;
		
		TextInteractionInitInfo copy(InteractionStack& interactionStack_) const;
		
		TextInteractionInitInfo copy(IPanelManager& panelManager_) const;
		
		TextInteractionInitInfo copy(Text& text_) const;
	};
}
