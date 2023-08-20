#pragma once

#include "../simple/keyEventSimple.hpp"
#include "../../../manager/interactionManager.hpp"

namespace ui {
	class AddInteractionEvent : public KeyEvent_Simple {
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
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
