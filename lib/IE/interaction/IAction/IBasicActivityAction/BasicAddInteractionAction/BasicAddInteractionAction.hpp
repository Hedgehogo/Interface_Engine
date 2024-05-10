#pragma once

#include "IE/utils/bool/ActiveTracker/ActiveTracker.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/interaction/IAction/IBasicTouchAction/IBasicTouchAction.hpp"
#include "../../../InteractionManager/InteractionManager.hpp"

namespace ie {
	template<typename T>
	class BasicAddInteractionAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicAddInteractionAction : public virtual IBasicTouchAction<T> {
			BoxPtr<IBasicInteraction<T> > interaction;
			
			BasicAddInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction);
			
			auto make(BasicActionInitInfo<T> init_info) -> ie::BasicAddInteractionAction<T>* override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicAddInteractionAction : public virtual IBasicTouchAction<T> {
	public:
		using Make = make_system::BasicAddInteractionAction<T>;
		
		BasicAddInteractionAction(Make&& make, BasicActionInitInfo<T> init_info);
		
		auto get_interaction() -> IBasicInteraction<T>&;
		
		auto update(sf::Vector2i point_position, bool active) -> void override;
		
		auto finish() -> void override;
	
	protected:
		ActiveTracker tracker_;
		InteractionManager* interaction_manager_;
		BoxPtr<IBasicInteraction<T> > interaction_;
	};
	
	using AddInteractionAction = BasicAddInteractionAction<>;
}

#include "BasicAddInteractionAction.inl"