#pragma once

#include "../IBasicBlockInteraction/IBasicBlockInteraction.hpp"
#include "../BasicOneKeyInteraction/BasicOneKeyInteraction.hpp"
#include "../../InteractionManager/InteractionManager.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicPressedInteraction : public BasicOneKeyInteraction<T>, public IBasicBlockInteraction<T> {
	public:
		BasicPressedInteraction(BoxPtr<BasicKeyEvent<T> >&& event, Key key);
		
		void init(BasicInteractionInitInfo<T> initInfo) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		BasicPressedInteraction<T>* copy() override;
	
	protected:
		InteractionManager* interactionManager;
	};
	
	using PressedInteraction = BasicPressedInteraction<>;
}

#include "BasicPressedInteraction.inl"
