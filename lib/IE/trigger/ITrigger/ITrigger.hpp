#pragma once

#include "../IAction/IBasicTouchAction/IBasicTouchAction.hpp"
#include "../IAction/IBasicActivityAction/BasicEmptyAction/BasicEmptyAction.hpp"
#include "../BasicActionInitInfo/BasicActionInitInfo.hpp"
#include "IE/initialization/make/make.hpp"
#include <box-ptr/BoxPtr.hpp>

namespace ie {
	using namespace bp;
	
	class TriggerManager;
	
	class ITrigger {
	public:
		enum class Priority {
			Highest,
			Medium,
			Lowest,
		};
		
		virtual auto is_prioritised() const -> bool;
		
		virtual auto get_priority() const -> Priority;
		
		virtual auto start() -> void = 0;
		
		virtual auto handle_event(Event event) -> bool = 0;
		
		virtual auto update() -> void = 0;
		
		virtual auto finish() -> void = 0;
		
		bool operator<(ITrigger& trigger) const;
		
		virtual ~ITrigger() = default;
	};
	
	template<typename T>
	class IBasicTrigger;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct IBasicTrigger {
			virtual auto make(BasicActionInitInfo<T> init_info) -> ie::IBasicTrigger<T>* = 0;
			
			virtual ~IBasicTrigger() = default;
		};
	}
	
	template<typename T = std::monostate>
	class IBasicTrigger : public virtual ITrigger {
	public:
		using Make = make_system::IBasicTrigger<T>;
	};
	
	using IBaseTrigger = IBasicTrigger<>;
}
