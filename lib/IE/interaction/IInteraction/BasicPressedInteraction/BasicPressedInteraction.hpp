#pragma once

#include "IE/interaction/IInteraction/BasicTouchInteraction/BasicTouchInteraction.hpp"
#include "../IBasicPrioritisedInteraction/IBasicPrioritisedInteraction.hpp"
#include "../../InteractionManager/InteractionManager.hpp"

namespace ie {
	template<typename T>
	class BasicPressedInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicPressedInteraction : public BasicTouchInteraction<T>, public virtual IBasicPrioritisedInteraction<T> {
			BasicPressedInteraction(BoxPtr<IBasicTouchAction<T> >&& action, Key key);
			
			auto make(BasicActionInitInfo<T> init_info) -> ie::BasicPressedInteraction<T>* override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicPressedInteraction : public BasicTouchInteraction<T>, public virtual IBasicPrioritisedInteraction<T> {
	public:
		using Make = make_system::BasicPressedInteraction<T>;
		
		BasicPressedInteraction(Make&& make, BasicActionInitInfo<T> init_info);
		
		auto update(sf::Vector2i mouse_position) -> void override;
		
	protected:
		InteractionManager* interaction_manager_;
	};
	
	using PressedInteraction = BasicPressedInteraction<>;
}

#include "BasicPressedInteraction.inl"
