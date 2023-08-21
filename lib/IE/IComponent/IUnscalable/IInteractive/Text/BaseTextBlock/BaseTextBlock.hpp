#pragma once

#include "../TextVariables/TextVariables.hpp"
#include "../BaseCharacter/BaseCharacter.hpp"
#include "../../../IScalable/IInteractive/BaseInteractive/BaseInteractive.hpp"
#include "../../../../InitInfo/InitInfo.hpp"

namespace ui {
	class BaseTextBlock {
	public:
		struct Edge {
			int start, end;
		};
	
		BaseTextBlock();
		
		BaseTextBlock(TextVariables textVariables);
		
		virtual ~BaseTextBlock() = default;
		
		void setTextVariables(sf::Color TextColor, sf::Color textSelectionColor, sf::Color backgroundSelectionColor, sf::Color inactiveTextSelectionColor, sf::Color inactiveBackgroundSelectionColor, sf::Font* font, uint size);
		
		virtual void init(InitInfo textInitInfo, InitInfo initInfo) = 0;
		
		virtual bool in(sf::Vector2f mousePosition) = 0;
		
		virtual std::vector<BaseCharacter*> getCharacters() = 0;
		
		virtual void update() = 0;
		
		virtual bool updateInteractions(sf::Vector2f mousePosition) = 0;
		
		virtual BaseTextBlock* copy() = 0;
	
	protected:
		TextVariables textVariables;
	};
}
