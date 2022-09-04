#pragma once
#include "../simple/buttonEventSimple.hpp"
#include "../../../interactionManager/interactionManager.hpp"

namespace ui {
	class AddInteractionEvent : public ButtonEvent_Simple {
	protected:
		IInteraction* interaction;
		InteractionManager* interactionManager;
		
		void startPressed(sf::Vector2i mousePosition) override;
		
		void stopPressed (sf::Vector2i mousePosition) override;
		
		void whilePressed(sf::Vector2i mousePosition) override;
		
		void whileNotPressed  (sf::Vector2i mousePosition) override;
		
		void copy(AddInteractionEvent* addInteractionEvent);
		
	public:
		explicit AddInteractionEvent(IInteraction& interaction);
		
		void init(InteractionManager &interactionManager);
		
		void setInteraction(IInteraction& interaction);
		
		AddInteractionEvent* copy() override;
	};
}
