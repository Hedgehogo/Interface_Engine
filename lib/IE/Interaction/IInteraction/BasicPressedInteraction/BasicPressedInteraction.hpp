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
			BasicPressedInteraction(BoxPtr<typename ie::BasicKeyAction<T>::Make>&& action, Key key);
			
			ie::BasicPressedInteraction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicPressedInteraction : public BasicOneKeyInteraction<T>, public virtual IBasicBlockInteraction<T> {
	public:
		using Make = make_system::BasicPressedInteraction<T>;
		
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
