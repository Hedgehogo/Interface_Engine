#pragma once

#include "../TextBlock/TextBlock.hpp"
#include "IE/Interaction/IInteraction/IInteraction.hpp"

namespace ie {
	class InteractiveTextBlock : public TextBlock {
	public:
		InteractiveTextBlock(
			BoxPtr<IBaseInteraction>&& interaction,
			std::u32string text,
			orl::Option<sf::Color> textColor = {},
			orl::Option<sf::Font*> font = {},
			orl::Option<sf::Text::Style> style = {},
			std::vector<BoxPtr<BaseLine>>&& lines = {},
			orl::Option<uint> size = {},
			orl::Option<sf::Color> textSelectionColor = {},
			orl::Option<sf::Color> backgroundSelectionColor = {},
			orl::Option<sf::Color> inactiveTextSelectionColor = {},
			orl::Option<sf::Color> inactiveBackgroundSelectionColor = {}
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