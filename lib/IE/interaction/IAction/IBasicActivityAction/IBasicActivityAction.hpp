#pragma once

#include <SFML/System/Vector2.hpp>
#include "../IAction.hpp"
#include "../../BasicActionInitInfo/BasicActionInitInfo.hpp"

namespace ie {
	template<typename A_>
	class IBasicActivityAction;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct IBasicActivityAction {
			virtual auto make(BasicActionInitInfo<A_> init_info) -> ie::IBasicActivityAction<A_>* = 0;
			
			virtual ~IBasicActivityAction() = default;
		};
	}
	
	template<typename A_ = std::monostate>
	class IBasicActivityAction : public virtual IAction {
	public:
		using Make = make_system::IBasicActivityAction<A_>;
		
		virtual auto update(bool active) -> void = 0;
	};
	
	using IActivityAction = IBasicActivityAction<>;
}
