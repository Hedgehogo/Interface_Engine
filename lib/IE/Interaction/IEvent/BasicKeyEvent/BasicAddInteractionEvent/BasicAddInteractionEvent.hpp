#pragma once

#include "IE/Interaction/IEvent/BasicKeyEvent/BasicBaseKeyEvent/BasicBaseKeyEvent.hpp"
#include "../../../InteractionManager/InteractionManager.hpp"

namespace ui {
	template<typename T = std::monostate>
	class BasicAddInteractionEvent : public BasicBaseKeyEvent<T> {
	public:
		explicit BasicAddInteractionEvent(IBaseInteraction& interaction);
		
		void init(BasicInteractionInitInfo<T> initInfo) override;
		
		void setInteraction(IBaseInteraction& interaction);
		
		BasicAddInteractionEvent<T>* copy() override;
	
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		InteractionManager* interactionManager;
		IBaseInteraction* interaction;
	};
	
	using AddInteractionEvent = BasicAddInteractionEvent<>;
}

#include "BasicAddInteractionEvent.inl"
