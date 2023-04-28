#pragma once

#include "../simple/keyEventSimple.hpp"
#include "../../../interactionManager/interactionManager.hpp"

namespace ui {
	class AddInteractionEvent : public KeyEvent_Simple {
	protected:
		IInteraction* interaction;
		InteractionManager* interactionManager;
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		void copy(AddInteractionEvent* addInteractionEvent);
	
	public:
		explicit AddInteractionEvent(IInteraction& interaction);
		
		void init(InteractionManager& interactionManager);
		
		void setInteraction(IInteraction& interaction);
		
		AddInteractionEvent* copy() override;
	};
}
