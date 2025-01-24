#pragma once

#include "IE/event/MouseWheel/MouseWheel.hpp"
#include "../IAction.hpp"
#include "../../BasicActionInitInfo/BasicActionInitInfo.hpp"

namespace ie {
	template<typename A_>
	class IBasicWheelAction;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct IBasicWheelAction {
			virtual auto make(BasicActionInitInfo<A_> init_info) -> ie::IBasicWheelAction<A_>* = 0;
			
			virtual ~IBasicWheelAction() = default;
		};
	}
	
	template<typename A_ = std::monostate>
	class IBasicWheelAction : public virtual IAction {
	public:
		using Make = make_system::IBasicWheelAction<A_>;
		
		virtual auto update(int value) -> void = 0;
	};
	
	using IWheelAction = IBasicWheelAction<>;
}