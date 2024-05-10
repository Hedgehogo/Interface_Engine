#pragma once

#include "../BasicAddInteractionAction.hpp"
#include "../../../../IInteraction/IBasicPrioritisedInteraction/IBasicPrioritisedInteraction.hpp"

namespace ie {
	template<typename T>
	class BasicAddPrioritisedInteractionAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicAddPrioritisedInteractionAction : public BasicAddInteractionAction<T> {
			BasicAddPrioritisedInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction);
			
			auto make(BasicActionInitInfo<T> init_info) -> ie::BasicAddPrioritisedInteractionAction<T>* override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicAddPrioritisedInteractionAction : public BasicAddInteractionAction<T> {
	public:
		using Make = make_system::BasicAddPrioritisedInteractionAction<T>;
		
		BasicAddPrioritisedInteractionAction(Make&& make, BasicActionInitInfo<T> init_info);
		
		auto update(bool active) -> void override;
		
		auto finish() -> void override;
	};
	
	using AddPrioritisedInteractionAction = BasicAddPrioritisedInteractionAction<std::monostate>;
}

#include "BasicAddPrioritisedInteractionAction.inl"