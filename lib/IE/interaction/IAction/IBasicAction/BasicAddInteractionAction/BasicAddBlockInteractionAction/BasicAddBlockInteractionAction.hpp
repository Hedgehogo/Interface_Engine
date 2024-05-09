#pragma once

#include "../BasicAddInteractionAction.hpp"
#include "../../../../IInteraction/IBasicPrioritisedInteraction/IBasicPrioritisedInteraction.hpp"

namespace ie {
	template<typename T>
	class BasicAddBlockInteractionAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicAddBlockInteractionAction : public BasicAddInteractionAction<T> {
			BasicAddBlockInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction);
			
			auto make(BasicActionInitInfo<T> init_info) -> ie::BasicAddBlockInteractionAction<T>* override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicAddBlockInteractionAction : public BasicAddInteractionAction<T> {
	public:
		using Make = make_system::BasicAddBlockInteractionAction<T>;
		
		BasicAddBlockInteractionAction(Make&& make, BasicActionInitInfo<T> init_info);
		
	protected:
		auto stop_pressed() -> void override;
		
		auto finish() -> void override;
	};
	
	using AddBlockInteractionAction = BasicAddBlockInteractionAction<std::monostate>;
}

#include "BasicAddBlockInteractionAction.inl"