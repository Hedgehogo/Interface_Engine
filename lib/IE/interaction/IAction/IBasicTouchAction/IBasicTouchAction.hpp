#pragma once

#include <SFML/System/Vector2.hpp>
#include "../IAction.hpp"
#include "../../BasicActionInitInfo/BasicActionInitInfo.hpp"

namespace ie {
	template<typename A_>
	class IBasicTouchAction;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct IBasicTouchAction {
			virtual auto make(BasicActionInitInfo<A_> init_info) -> ie::IBasicTouchAction<A_>* = 0;
			
			virtual ~IBasicTouchAction() = default;
		};
	}
	
	template<typename A_ = std::monostate>
	class IBasicTouchAction : public virtual IAction {
	public:
		using Make = make_system::IBasicTouchAction<A_>;
		
		virtual auto update(sf::Vector2i point_position, bool active) -> void = 0;
	};
	
	using ITouchAction = IBasicTouchAction<std::monostate>;
}
