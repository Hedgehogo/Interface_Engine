#pragma once

#include "../BasicKeyAction.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicEmptyAction : public BasicKeyAction<T> {
	public:
		struct Make : public BasicKeyAction<T>::Make {
			BasicEmptyAction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
		
		BasicEmptyAction(Make&& make, BasicActionInitInfo<T> initInfo);
		
		BasicEmptyAction();
		
		void update(sf::Vector2i, bool) override;
		
		BasicEmptyAction<T>* copy() override;
	};
	
	using EmptyAction = BasicEmptyAction<>;
}

#include "BasicEmptyAction.inl"
