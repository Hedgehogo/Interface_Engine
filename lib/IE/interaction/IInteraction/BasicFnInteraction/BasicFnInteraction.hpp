#pragma once

#include "../IInteraction.hpp"
#include <functional>

namespace ie {
	template<typename T>
	class BasicFnInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicFnInteraction : public virtual IBasicInteraction<T> {
			using FnType = std::function<void(sf::Vector2i mouse_position)>;
			
			FnType start_fn;
			FnType finish_fn;
			
			BasicFnInteraction() = default;
			
			BasicFnInteraction(FnType start_fn, FnType finish_fn);
			
			ie::BasicFnInteraction<T>* make(BasicActionInitInfo<T> init_info) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicFnInteraction : public virtual IBasicInteraction<T> {
	public:
		using FnType = std::function<void(sf::Vector2i mouse_position)>;
		using Make = make_system::BasicFnInteraction<T>;
		
		BasicFnInteraction(Make&& make, BasicActionInitInfo<T> init_info);
		
		BasicFnInteraction(FnType start_fn, FnType finish_fn);
		
		void start(sf::Vector2i mouse_position) override;
		
		void finish(sf::Vector2i mouse_position) override;
	
	protected:
		FnType start_fn;
		FnType finish_fn;
	};
	
	using FnInteraction = BasicFnInteraction<>;
}

#include "BasicFnInteraction.inl"
