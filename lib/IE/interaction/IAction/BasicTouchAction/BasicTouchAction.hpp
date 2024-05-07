#pragma once

#include <SFML/System/Vector2.hpp>
#include "../IAction.hpp"
#include "../../BasicActionInitInfo/BasicActionInitInfo.hpp"

namespace ie {
	template<typename T>
	class BasicTouchAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicTouchAction {
			virtual auto make(BasicActionInitInfo<T> init_info) -> ie::BasicTouchAction<T>* = 0;
			
			virtual ~BasicTouchAction() = default;
		};
	}
	
	template<typename T = std::monostate>
	class BasicTouchAction : public virtual IAction {
	public:
		using Make = make_system::BasicTouchAction<T>;
		
		explicit BasicTouchAction();
		
		virtual auto set_pressed(bool pressed) -> void;
		
		virtual auto update(sf::Vector2i point_position, bool press) -> void = 0;
		
	protected:
		bool pressed_;
	};
	
	using TouchAction = BasicTouchAction<std::monostate>;
}

#include "BasicTouchAction.inl"