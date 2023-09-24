#pragma once

#include "../TextBlock/TextBlock.hpp"
#include "IE/Interaction/IInteraction/IInteraction.hpp"

namespace ie {
	class InteractiveTextBlock : public TextBlock {
	public:
		struct Make : public TextBlock::Make {
			BoxPtr<IBaseInteraction> interaction;
			
			Make(BoxPtr<IBaseInteraction>&& interaction,
				 const std::u32string& text,
				 const orl::Option<sf::Color>& textColor = {},
				 const orl::Option<sf::Font*>& font = {},
				 const orl::Option<sf::Text::Style>& style = {},
				 std::vector<BoxPtr<BaseLine::Make>>&& lines = {},
				 const orl::Option<uint>& size = {},
				 const orl::Option<sf::Color>& textSelectionColor = {},
				 const orl::Option<sf::Color>& backgroundSelectionColor = {},
				 const orl::Option<sf::Color>& inactiveTextSelectionColor = {},
				 const orl::Option<sf::Color>& inactiveBackgroundSelectionColor = {}
			);
			
			InteractiveTextBlock* make(TextBockInitInfo textBlockInitInfo) override;
		};
		
		InteractiveTextBlock(Make&& make, TextBockInitInfo textBlockInitInfo);
		
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
		
		void init(TextBockInitInfo textBlockInitInfo);
		
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