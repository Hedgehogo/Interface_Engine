#pragma once

#include "../BasicAddInteractionAction.hpp"
#include "IE/Interaction/IInteraction/IBasicBlockInteraction/IBasicBlockInteraction.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicAddBlockInteractionAction : public BasicAddInteractionAction<T> {
	public:
		struct Make : public BasicAddInteractionAction<T>::Make {
			Make(BoxPtr<typename IBasicInteraction<T>::Make>&& interaction);
			
			BasicAddBlockInteractionAction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
		
		BasicAddBlockInteractionAction(Make&& make, BasicActionInitInfo<T> initInfo);
		
		explicit BasicAddBlockInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction);
		
		BasicAddBlockInteractionAction<T>* copy() override;
	
	protected:
		void stopPressed() override;
	};
	
	using AddBlockInteractionAction = BasicAddBlockInteractionAction<std::monostate>;
}

#include "BasicAddBlockInteractionAction.inl"
