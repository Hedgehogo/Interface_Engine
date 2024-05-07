#pragma once

#include <SFML/System/Vector2.hpp>
#include "../IAction.hpp"
#include "../../BasicActionInitInfo/BasicActionInitInfo.hpp"

namespace ie {
	template<typename A_>
	class IBasicAction;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct IBasicAction {
			virtual auto make(BasicActionInitInfo<A_> init_info) -> ie::IBasicAction<A_>* = 0;
			
			virtual ~IBasicAction() = default;
		};
	}
	
	template<typename A_>
	class IBasicAction : public virtual IAction {
	public:
		using Make = make_system::IBasicAction<A_>;
		
		virtual auto update(bool active) -> void = 0;
	};
}
