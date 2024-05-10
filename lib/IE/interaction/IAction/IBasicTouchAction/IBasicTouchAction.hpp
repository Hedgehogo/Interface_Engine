#pragma once

#include <SFML/System/Vector2.hpp>
#include "../IAction.hpp"
#include "../../BasicActionInitInfo/BasicActionInitInfo.hpp"

namespace ie {
	template<typename T>
	class IBasicTouchAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct IBasicTouchAction {
			virtual auto make(BasicActionInitInfo<T> init_info) -> ie::IBasicTouchAction<T>* = 0;
			
			virtual ~IBasicTouchAction() = default;
		};
	}
	
	template<typename T = std::monostate>
	class IBasicTouchAction : public virtual IAction {
	public:
		using Make = make_system::IBasicTouchAction<T>;
		
		virtual auto update(sf::Vector2i point_position, bool active) -> void = 0;
	};
	
	using ITouchAction = IBasicTouchAction<std::monostate>;
}
