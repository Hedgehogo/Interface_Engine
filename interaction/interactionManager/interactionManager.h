#pragma once

#include "../iInteraction/iInteraction.h"

namespace ui {
	class InteractionManager {
	protected:
		sf::RenderWindow &window;
		std::vector<IInteraction *> interactions;
		std::vector<IInteraction *> addInteractions;
		std::vector<IInteraction *> deleteInteractions;
		sf::Vector2i position;
		bool block;
	
	public:
		explicit InteractionManager(sf::RenderWindow &window);
		
		void addInteraction(IInteraction &interaction);
		
		void deleteInteraction(IInteraction &interaction);
		
		void clear();
		
		bool isBlocked();
		
		virtual void update(sf::Vector2i mousePosition);
	};
}

#include "../iInteraction/empty/emptyInteraction.h"
#include "../iInteraction/lambda/lambdaInteraction.h"
#include "../iInteraction/mouse/mouseInteraction.h"
#include "../iInteraction/mouse/lambda/mouseLambdaInteraction.h"
