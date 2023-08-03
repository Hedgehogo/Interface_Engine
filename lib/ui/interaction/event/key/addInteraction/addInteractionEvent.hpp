#pragma once

#include "../simple/keyEventSimple.hpp"
#include "../../../interactionManager/interactionManager.hpp"

namespace ui {
	class AddInteractionEvent : public KeyEvent_Simple {
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		void copy(AddInteractionEvent* addInteractionEvent);
	
	public:
		explicit AddInteractionEvent(IInteraction& interaction);
		
		void init(InteractionInitInfo interactionInitInfo) override;
		
		void setInteraction(IInteraction& interaction);
		
		AddInteractionEvent* copy() override;
	
	protected:
		InteractionManager* interactionManager;
		IInteraction* interaction;
	};
}
