#pragma once

#include "../IBasicBlockInteraction/IBasicBlockInteraction.hpp"
#include "../BasicOneKeyInteraction/BasicOneKeyInteraction.hpp"
#include "../../InteractionManager/InteractionManager.hpp"

namespace ie {
	template<typename T>
	class BasicPressedInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicPressedInteraction : public BasicOneKeyInteraction<T>, public virtual IBasicBlockInteraction<T> {
			BasicPressedInteraction(BoxPtr<BasicKeyAction<T> >&& action, Key key);
			
			ie::BasicPressedInteraction<T>* make(BasicActionInitInfo<T> init_info) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicPressedInteraction : public BasicOneKeyInteraction<T>, public virtual IBasicBlockInteraction<T> {
	public:
		using Make = make_system::BasicPressedInteraction<T>;
		
		BasicPressedInteraction(Make&& make, BasicActionInitInfo<T> init_info);
		
		BasicPressedInteraction(BoxPtr<BasicKeyAction<T> >&& action, Key key);
		
		void init(BasicActionInitInfo<T> init_info) override;
		
		void update(sf::Vector2i mouse_position) override;
		
		BasicPressedInteraction<T>* copy() override;
	
	protected:
		InteractionManager* interaction_manager_;
	};
	
	using PressedInteraction = BasicPressedInteraction<>;
}

#include "BasicPressedInteraction.inl"
