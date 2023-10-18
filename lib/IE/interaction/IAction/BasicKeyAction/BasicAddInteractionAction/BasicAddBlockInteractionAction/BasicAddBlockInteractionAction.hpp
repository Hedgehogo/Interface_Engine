#pragma once

#include "../BasicAddInteractionAction.hpp"
#include "../../../../IInteraction/IBasicBlockInteraction/IBasicBlockInteraction.hpp"

namespace ie {
	template<typename T>
	class BasicAddBlockInteractionAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicAddBlockInteractionAction : public BasicAddInteractionAction<T> {
			BasicAddBlockInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction);
			
			ie::BasicAddBlockInteractionAction<T>* make(BasicActionInitInfo<T> init_info) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicAddBlockInteractionAction : public BasicAddInteractionAction<T> {
	public:
		using Make = make_system::BasicAddBlockInteractionAction<T>;
		
		BasicAddBlockInteractionAction(Make&& make, BasicActionInitInfo<T> init_info);
		
		explicit BasicAddBlockInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction);
		
		BasicAddBlockInteractionAction<T>* copy() override;
	
	protected:
		void stop_pressed() override;
	};
	
	using AddBlockInteractionAction = BasicAddBlockInteractionAction<std::monostate>;
}

#include "BasicAddBlockInteractionAction.inl"