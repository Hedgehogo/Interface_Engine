#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "IE/component/IComponent/InitInfo/InitInfo.hpp"
#include "IE/component/IComponent/InitInfo/InitInfo.hpp"
#include "../../TextVariables/TextVariables.hpp"

namespace ie {
	struct TextBockInitInfo : public InitInfo{
		sf::RenderTarget& textRenderTarget;
		DrawManager& textDrawManager;
		InteractionManager& textInteractionManager;
		TextVariables& textVariables;
		
		TextBockInitInfo(
			sf::RenderWindow& window,
			sf::RenderTarget& renderTarget,
			DrawManager& drawManager,
			UpdateManager& updateManager,
			InteractionManager& interactionManager,
			InteractionStack& interactionStack,
			IPanelManager& panelManager,
			sf::RenderTarget& textRenderTarget,
			DrawManager& textDrawManager,
			InteractionManager& textInteractionManager,
			TextVariables& textVariables
		);
		
		TextBockInitInfo(InitInfo initInfo, sf::RenderTarget& textRenderTarget, DrawManager& textDrawManager, InteractionManager& textInteractionManager, TextVariables&& textVariables);
	};
}
