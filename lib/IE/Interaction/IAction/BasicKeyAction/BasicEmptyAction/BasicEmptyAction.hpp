#pragma once

#include "../BasicKeyAction.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicEmptyAction : public BasicKeyAction<T> {
	public:
		BasicEmptyAction();
		
		void update(sf::Vector2i, bool) override;
		
		BasicEmptyAction<T>* copy() override;
	};
	
	using EmptyAction = BasicEmptyAction<>;
}

#include "BasicEmptyAction.inl"
