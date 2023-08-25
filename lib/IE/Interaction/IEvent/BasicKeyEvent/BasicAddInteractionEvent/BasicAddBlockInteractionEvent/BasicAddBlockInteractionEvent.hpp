#pragma once

#include "../BasicAddInteractionEvent.hpp"
#include "IE/Interaction/IInteraction/IBasicBlockInteraction/IBasicBlockInteraction.hpp"

namespace ui {
	template<typename T = std::monostate>
	class BasicAddBlockInteractionEvent : public BasicAddInteractionEvent<T> {
	public:
		explicit BasicAddBlockInteractionEvent(IBasicInteraction<T>& interaction);
		
		BasicAddBlockInteractionEvent<T>* copy() override;
	
	protected:
		void stopPressed() override;
	};
	
	using AddBlockInteractionEvent = BasicAddBlockInteractionEvent<std::monostate>;
}

#include "BasicAddBlockInteractionEvent.inl"
