#pragma once

#include "IE/Interaction/IEvent/BasicKeyEvent/BasicBaseKeyEvent/BasicBaseKeyEvent.hpp"
#include "../../../InteractionManager/InteractionManager.hpp"

namespace ui {
	template<typename T = std::monostate>
	class BasicAddInteractionEvent : public BasicBaseKeyEvent<T> {
	public:
		explicit BasicAddInteractionEvent(IBasicInteraction<T>& interaction);
		
		void init(BasicInteractionInitInfo<T> initInfo) override;
		
		void setInteraction(IBasicInteraction<T>& interaction);
		
		BasicAddInteractionEvent<T>* copy() override;
	
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		InteractionManager* interactionManager;
		IBasicInteraction<T>* interaction;
	};
	
	using AddInteractionEvent = BasicAddInteractionEvent<>;
}

#include "BasicAddInteractionEvent.inl"
