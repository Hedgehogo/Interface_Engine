#pragma once

#include "../TextBlock/TextBlock.hpp"
#include "IE/Interaction/IInteraction/IInteraction.hpp"

namespace ie {
	class InteractiveTextBlock : public TextBlock {
	public:
		InteractiveTextBlock(
			BoxPtr<IBaseInteraction>&& interaction, std::u32string text, sf::Color textColor = nullColor,
			sf::Font* font = nullptr, sf::Text::Style style = {}, std::vector<BoxPtr<BaseLine>>&& lines = {}, int size = 0,
			sf::Color textSelectionColor = nullColor,
			sf::Color backgroundSelectionColor = nullColor,
			sf::Color inactiveTextSelectionColor = nullColor,
			sf::Color inactiveBackgroundSelectionColor = nullColor
		);
		
		void init(InitInfo textInitInfo, InitInfo initInfo);
		
		bool in(sf::Vector2f mousePosition);
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f) override;
	
		InteractiveTextBlock* copy() override;
	
	protected:
		InteractionManager* interactionManager;
		
		bool interact;
		bool oldInteract;
		
		BoxPtr<IInteraction> interaction;
	};
	
	template<>
	struct DecodePointer<InteractiveTextBlock> {
		static bool decodePointer(const YAML::Node& node, InteractiveTextBlock*& interactiveTextBlock);
	};
}