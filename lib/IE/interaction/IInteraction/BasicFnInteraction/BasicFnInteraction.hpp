#pragma once

#include "../IInteraction.hpp"
#include <functional>

namespace ie {
	template<typename T>
	class BasicFnInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicFnInteraction : public virtual IBasicInteraction<T> {
			using FnType = std::function<void(sf::Vector2i mousePosition)>;
			
			FnType startFn;
			FnType finishFn;
			
			BasicFnInteraction() = default;
			
			BasicFnInteraction(FnType startFn, FnType finishFn);
			
			ie::BasicFnInteraction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicFnInteraction : public virtual IBasicInteraction<T> {
	public:
		using FnType = std::function<void(sf::Vector2i mousePosition)>;
		using Make = make_system::BasicFnInteraction<T>;
		
		BasicFnInteraction(Make&& make, BasicActionInitInfo<T> initInfo);
		
		BasicFnInteraction(FnType startFn, FnType finishFn);
		
		void start(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
	
	protected:
		FnType startFn;
		FnType finishFn;
	};
	
	using FnInteraction = BasicFnInteraction<>;
}

#include "BasicFnInteraction.inl"
