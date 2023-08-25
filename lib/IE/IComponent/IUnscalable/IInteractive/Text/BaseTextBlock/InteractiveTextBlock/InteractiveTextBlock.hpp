#pragma once

#include "../TextBlock/TextBlock.hpp"
#include "../../../../../../Interaction/IInteraction/IInteraction.hpp"

namespace ui {
	class InteractiveTextBlock : public TextBlock {
	public:
		InteractiveTextBlock(
			IBaseInteraction* interaction, std::u32string text, sf::Color textColor = nullColor,
			sf::Font* font = nullptr, sf::Text::Style style = {}, std::vector<BaseLine*> lines = {}, int size = 0,
			sf::Color textSelectionColor = nullColor,
			sf::Color backgroundSelectionColor = nullColor,
			sf::Color inactiveTextSelectionColor = nullColor,
			sf::Color inactiveBackgroundSelectionColor = nullColor
		);
		
		InteractiveTextBlock(
			int indexInteraction, std::u32string text, sf::Color textColor = nullColor,
			sf::Font* font = nullptr, sf::Text::Style style = {}, std::vector<BaseLine*> lines = {}, int size = 0,
			sf::Color textSelectionColor = nullColor,
			sf::Color backgroundSelectionColor = nullColor,
			sf::Color inactiveTextSelectionColor = nullColor,
			sf::Color inactiveBackgroundSelectionColor = nullColor
		);
		
		~InteractiveTextBlock();
		
		void init(InitInfo textInitInfo, InitInfo initInfo);
		
		std::vector<BaseCharacter*> getCharacters() override;
		
		bool in(sf::Vector2f mousePosition);
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f) override;
	
	protected:
		InteractiveTextBlock(std::u32string str, TextVariables textVariables, IBaseInteraction* interaction);
		
		InteractiveTextBlock(std::u32string str, TextVariables textVariables, int indexInteraction);
	
	public:
		InteractiveTextBlock* copy() override;
	
	protected:
		InteractionManager* interactionManager;
		
		bool interact;
		bool oldInteract;
		
		int indexInteraction;
		IInteraction* interaction;
	};
	
	template<>
	struct DecodePointer<InteractiveTextBlock> {
		static bool decodePointer(const YAML::Node& node, InteractiveTextBlock*& interactiveTextBlock);
	};
}