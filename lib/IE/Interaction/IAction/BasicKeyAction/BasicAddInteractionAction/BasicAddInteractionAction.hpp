#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "../../../InteractionManager/InteractionManager.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicAddInteractionAction : public BasicBaseKeyAction<T> {
	public:
		struct Make : public virtual BasicKeyAction<T>::Make {
			BoxPtr<typename IBasicInteraction<T>::Make> interaction;
			
			Make(BoxPtr<typename IBasicInteraction<T>::Make>&& interaction);
			
			BasicAddInteractionAction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
		
		BasicAddInteractionAction(Make&& make, BasicActionInitInfo<T> initInfo);
		
		explicit BasicAddInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction);
		
		void init(BasicActionInitInfo<T> initInfo) override;
		
		IBasicInteraction<T>& getInteraction();
		
		BasicAddInteractionAction<T>* copy() override;
	
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		InteractionManager* interactionManager;
		BoxPtr<IBasicInteraction<T> > interaction;
	};
	
	using AddInteractionAction = BasicAddInteractionAction<>;
}

#include "BasicAddInteractionAction.inl"
