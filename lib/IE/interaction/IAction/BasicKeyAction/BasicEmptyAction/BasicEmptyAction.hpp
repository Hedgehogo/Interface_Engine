#pragma once

#include "../BasicKeyAction.hpp"

namespace ie {
	template<typename T>
	class BasicEmptyAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicEmptyAction : public BasicKeyAction<T> {
			auto make(BasicActionInitInfo<T> init_info) -> ie::BasicEmptyAction<T>* override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicEmptyAction : public virtual BasicKeyAction<T> {
	public:
		using Make = make_system::BasicEmptyAction<T>;
		
		BasicEmptyAction(Make&& make, BasicActionInitInfo<T> init_info);
		
		BasicEmptyAction();
		
		auto update(sf::Vector2i, bool) -> void override;
	};
	
	using EmptyAction = BasicEmptyAction<>;
}

#include "BasicEmptyAction.inl"
