#pragma once

#include "../BasicBaseTouchAction/BasicBaseTouchAction.hpp"
#include "../../../InteractionManager/InteractionManager.hpp"

namespace ie {
	template<typename T>
	class BasicAddInteractionAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicAddInteractionAction : public BasicTouchAction<T> {
			BoxPtr<IBasicInteraction<T> > interaction;
			
			BasicAddInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction);
			
			auto make(BasicActionInitInfo<T> init_info) -> ie::BasicAddInteractionAction<T>* override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicAddInteractionAction : public BasicBaseTouchAction<T> {
	public:
		using Make = make_system::BasicAddInteractionAction<T>;
		
		BasicAddInteractionAction(Make&& make, BasicActionInitInfo<T> init_info);
		
		auto get_interaction() -> IBasicInteraction<T>&;
		
	protected:
		auto start_pressed() -> void override;
		
		auto stop_pressed() -> void override;
		
		auto while_pressed() -> void override;
		
		auto while_not_pressed() -> void override;
		
		auto finish() -> void override;
		
		InteractionManager* interaction_manager_;
		BoxPtr<IBasicInteraction<T> > interaction_;
	};
	
	using AddInteractionAction = BasicAddInteractionAction<>;
}

#include "BasicAddInteractionAction.inl"