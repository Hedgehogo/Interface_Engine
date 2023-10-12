#include "TextBockInitInfo.hpp"

namespace ie {
	TextBockInitInfo::TextBockInitInfo(
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
	) : InitInfo(
			window,
			renderTarget,
			drawManager,
			updateManager,
			interactionManager,
			interactionStack,
			panelManager
		),
		textRenderTarget(textRenderTarget),
		textDrawManager(textDrawManager),
		textInteractionManager(textInteractionManager),
		textVariables(textVariables) {
	}
	
	TextBockInitInfo::TextBockInitInfo(
		InitInfo initInfo,
		sf::RenderTarget& textRenderTarget,
		DrawManager& textDrawManager,
		InteractionManager& textInteractionManager,
		TextVariables&& textVariables
	) : InitInfo(initInfo),
		textRenderTarget(textRenderTarget),
		textDrawManager(textDrawManager),
		textInteractionManager(textInteractionManager),
		textVariables(textVariables) {
	
	}
}