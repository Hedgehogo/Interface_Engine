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
			
			auto make(BasicActionInitInfo<T> init_info) -> ie::BasicFnInteraction<T>* override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicFnInteraction : public virtual IBasicInteraction<T> {
	public:
		using FnType = std::function<void(sf::Vector2i point_position)>;
		using Make = make_system::BasicFnInteraction<T>;
		
		BasicFnInteraction(Make&& make, BasicActionInitInfo<T> init_info);
		
		BasicFnInteraction(FnType start_fn, FnType finish_fn);
		
		auto start(sf::Vector2i mouse_position) -> void override;
		
		auto finish(sf::Vector2i mouse_position) -> void override;
	
	protected:
		FnType start_fn_;
		FnType finish_fn_;
	};
	
	using FnInteraction = BasicFnInteraction<>;
}

#include "BasicFnInteraction.inl"
