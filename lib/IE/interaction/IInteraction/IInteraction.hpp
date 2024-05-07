#pragma once

#include "../IAction/BasicTouchAction/BasicFnTouchAction/BasicFnTouchAction.hpp"
#include "../IAction/BasicTouchAction/BasicEmptyAction/BasicEmptyAction.hpp"
#include "../BasicActionInitInfo/BasicActionInitInfo.hpp"
#include "IE/initialization/make/make.hpp"
#include <box-ptr/BoxPtr.hpp>

namespace ie {
	using namespace bp;
	
	class InteractionManager;
	
	class IInteraction {
	public:
		enum class Priority {
			Highest,
			Medium,
			Lowest,
		};
		
		virtual auto is_blocked() const -> bool;
		
		virtual auto get_priority() const -> Priority;
		
		virtual auto start(sf::Vector2i mouse_position) -> void = 0;
		
		virtual auto update(sf::Vector2i mouse_position) -> void = 0;
		
		virtual auto finish(sf::Vector2i mouse_position) -> void = 0;
		
		bool operator<(IInteraction& interaction) const;
		
		virtual ~IInteraction() = default;
	};
	
	template<typename T>
	class IBasicInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct IBasicInteraction {
			virtual auto make(BasicActionInitInfo<T> init_info) -> ie::IBasicInteraction<T>* = 0;
			
			virtual ~IBasicInteraction() = default;
		};
	}
	
	template<typename T = std::monostate>
	class IBasicInteraction : public virtual IInteraction {
	public:
		using Make = make_system::IBasicInteraction<T>;
	};
	
	using IBaseInteraction = IBasicInteraction<>;
}
