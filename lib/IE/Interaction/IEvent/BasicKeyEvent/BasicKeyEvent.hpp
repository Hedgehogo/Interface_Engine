#pragma once

#include <SFML/System/Vector2.hpp>
#include "../IEvent.hpp"
#include "IE/Interaction/BasicInteractionInitInfo/BasicInteractionInitInfo.hpp"

namespace ui {
	template<typename T = std::monostate>
	class BasicKeyEvent : public IEvent {
	public:
		explicit BasicKeyEvent();
		
		virtual void init(BasicInteractionInitInfo<T> initInfo);
		
		virtual void setPressed(bool pressed);
		
		virtual void update(sf::Vector2i mousePosition, bool press) = 0;
		
		virtual BasicKeyEvent* copy() = 0;
	
	protected:
		bool pressed;
	};
	
	using KeyEvent = BasicKeyEvent<std::monostate>;
}

#include "BasicKeyEvent.inl"
