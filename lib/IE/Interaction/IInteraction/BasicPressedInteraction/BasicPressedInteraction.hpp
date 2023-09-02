#pragma once

#include "../IBasicBlockInteraction/IBasicBlockInteraction.hpp"
#include "../BasicOneKeyInteraction/BasicOneKeyInteraction.hpp"
#include "../../InteractionManager/InteractionManager.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicPressedInteraction : public BasicOneKeyInteraction<T>, public virtual IBasicBlockInteraction<T> {
	public:
		struct Make : public BasicOneKeyInteraction<T>::Make, public virtual IBasicBlockInteraction<T>::Make {
			Make(BoxPtr<typename BasicKeyAction<T>::Make>&& action, Key key);
			
			BasicPressedInteraction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
		
		BasicPressedInteraction(Make&& make, BasicActionInitInfo<T> initInfo);
		
		BasicPressedInteraction(BoxPtr<BasicKeyAction<T> >&& action, Key key);
		
		void init(BasicActionInitInfo<T> initInfo) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		BasicPressedInteraction<T>* copy() override;
	
	protected:
		InteractionManager* interactionManager;
	};
	
	using PressedInteraction = BasicPressedInteraction<>;
}

#include "BasicPressedInteraction.inl"
