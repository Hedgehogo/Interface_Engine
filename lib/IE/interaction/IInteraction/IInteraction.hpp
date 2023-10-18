#pragma once

#include "../IAction/BasicKeyAction/BasicEmptyAction/BasicEmptyAction.hpp"
#include "../IAction/BasicKeyAction/BasicFnKeyAction/BasicFnKeyAction.hpp"
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
		
		virtual ~IInteraction() = default;
		
		virtual bool is_blocked() const;
		
		virtual Priority get_priority() const;
		
		virtual void start(sf::Vector2i mouse_position) = 0;
		
		virtual void update(sf::Vector2i mouse_position) = 0;
		
		virtual void finish(sf::Vector2i mouse_position) = 0;
		
		bool operator<(IInteraction& interaction) const;
		
		virtual IInteraction* copy() = 0;
	};
	
	template<typename T>
	class IBasicInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct IBasicInteraction {
			virtual ie::IBasicInteraction<T>* make(BasicActionInitInfo<T> init_info) = 0;
			
			virtual ~IBasicInteraction() = default;
		};
	}
	
	template<typename T = std::monostate>
	class IBasicInteraction : public virtual IInteraction {
	public:
		using Make = make_system::IBasicInteraction<T>;
		
		virtual void init(BasicActionInitInfo<T> init_info);
		
		virtual IBasicInteraction<T>* copy() = 0;
	};
	
	using IBaseInteraction = IBasicInteraction<>;
}

#include "IInteraction.inl"