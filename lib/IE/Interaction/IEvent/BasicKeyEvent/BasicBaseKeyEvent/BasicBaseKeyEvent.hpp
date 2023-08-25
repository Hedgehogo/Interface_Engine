#pragma once

#include "../BasicKeyEvent.hpp"

namespace ui {
	template<typename T = std::monostate>
	class BasicBaseKeyEvent : public virtual BasicKeyEvent<T> {
	public:
		BasicBaseKeyEvent();
		
		void init(BasicInteractionInitInfo<T> initInfo) override;
		
		void setPressed(bool pressed) override;
		
		void update(sf::Vector2i mousePosition, bool press) override;
	
	protected:
		virtual void startPressed() = 0;
		
		virtual void stopPressed() = 0;
		
		virtual void whilePressed() = 0;
		
		virtual void whileNotPressed() = 0;
		
		sf::Vector2i mousePosition;
	};
	
	using BaseKeyEvent = BasicBaseKeyEvent<>;
}

#include "BasicBaseKeyEvent.inl"
