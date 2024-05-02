#pragma once

#include <SFML/System/Vector2.hpp>
#include "../IAction.hpp"
#include "../../BasicActionInitInfo/BasicActionInitInfo.hpp"

namespace ie {
	template<typename T>
	class BasicKeyAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicKeyAction {
			virtual auto make(BasicActionInitInfo<T> init_info) -> ie::BasicKeyAction<T>* = 0;
			
			virtual ~BasicKeyAction() = default;
		};
	}
	
	template<typename T = std::monostate>
	class BasicKeyAction : public virtual IAction {
	public:
		using Make = make_system::BasicKeyAction<T>;
		
		explicit BasicKeyAction();
		
		virtual auto set_pressed(bool pressed) -> void;
		
		virtual auto update(sf::Vector2i point_position, bool press) -> void = 0;
		
	protected:
		bool pressed_;
	};
	
	using KeyAction = BasicKeyAction<std::monostate>;
}

#include "BasicKeyAction.inl"