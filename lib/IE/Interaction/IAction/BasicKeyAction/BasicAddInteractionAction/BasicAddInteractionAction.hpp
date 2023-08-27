#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "../../../InteractionManager/InteractionManager.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicAddInteractionAction : public BasicBaseKeyAction<T> {
	public:
		explicit BasicAddInteractionAction(IBasicInteraction<T>& interaction);
		
		void init(BasicActionInitInfo<T> initInfo) override;
		
		void setInteraction(IBasicInteraction<T>& interaction);
		
		BasicAddInteractionAction<T>* copy() override;
	
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		InteractionManager* interactionManager;
		IBasicInteraction<T>* interaction;
	};
	
	using AddInteractionAction = BasicAddInteractionAction<>;
}

#include "BasicAddInteractionAction.inl"
