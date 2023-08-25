#pragma once

#include "../BasicKeyEvent.hpp"

namespace ui {
	template<typename T = std::monostate>
	class BasicEmptyEvent : public BasicKeyEvent<T> {
	public:
		BasicEmptyEvent();
		
		void update(sf::Vector2i, bool) override;
		
		BasicEmptyEvent<T>* copy() override;
	};
	
	using EmptyEvent = BasicEmptyEvent<>;
}

#include "BasicEmptyEvent.inl"
