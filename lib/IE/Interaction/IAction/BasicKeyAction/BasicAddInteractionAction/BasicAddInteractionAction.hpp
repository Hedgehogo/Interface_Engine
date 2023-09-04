#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "../../../InteractionManager/InteractionManager.hpp"

namespace ie {
	template<typename T>
	class BasicAddInteractionAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicAddInteractionAction : public BasicKeyAction<T> {
			BoxPtr<IBasicInteraction<T> > interaction;
			
			BasicAddInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction);
			
			ie::BasicAddInteractionAction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicAddInteractionAction : public BasicBaseKeyAction<T> {
	public:
		using Make = make_system::BasicAddInteractionAction<T>;
		
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
