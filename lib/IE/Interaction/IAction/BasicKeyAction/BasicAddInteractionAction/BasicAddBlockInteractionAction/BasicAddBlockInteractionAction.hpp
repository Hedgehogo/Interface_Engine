#pragma once

#include "../BasicAddInteractionAction.hpp"
#include "IE/Interaction/IInteraction/IBasicBlockInteraction/IBasicBlockInteraction.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicAddBlockInteractionAction : public BasicAddInteractionAction<T> {
	public:
		explicit BasicAddBlockInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction);
		
		BasicAddBlockInteractionAction<T>* copy() override;
	
	protected:
		void stopPressed() override;
	};
	
	using AddBlockInteractionAction = BasicAddBlockInteractionAction<std::monostate>;
}

#include "BasicAddBlockInteractionAction.inl"
