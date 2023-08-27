#pragma once

#include <SFML/System/Vector2.hpp>
#include "../IAction.hpp"
#include "IE/Interaction/BasicInteractionInitInfo/BasicInteractionInitInfo.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicKeyAction : public IAction {
	public:
		explicit BasicKeyAction();
		
		virtual void init(BasicInteractionInitInfo<T> initInfo);
		
		virtual void setPressed(bool pressed);
		
		virtual void update(sf::Vector2i mousePosition, bool press) = 0;
		
		virtual BasicKeyAction* copy() = 0;
	
	protected:
		bool pressed;
	};
	
	using KeyAction = BasicKeyAction<std::monostate>;
}

#include "BasicKeyAction.inl"
