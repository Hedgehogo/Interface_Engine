#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicEmptyAction/BasicEmptyAction.hpp"
#include "IE/Interaction/IAction/BasicKeyAction/BasicLambdaKeyAction/BasicLambdaKeyAction.hpp"
#include "IE/Interaction/BasicActionInitInfo/BasicActionInitInfo.hpp"
#include "IE/Make/make.hpp"
#include <Box_Ptr/boxPtr.hpp>

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
		
		virtual bool isBlocked() const;
		
		virtual Priority getPriority() const;
		
		virtual void start(sf::Vector2i mousePosition) = 0;
		
		virtual void update(sf::Vector2i mousePosition) = 0;
		
		virtual void finish(sf::Vector2i mousePosition) = 0;
		
		bool operator<(IInteraction& interaction) const;
		
		virtual IInteraction* copy() = 0;
	};
	
	template<typename T = std::monostate>
	class IBasicInteraction : public virtual IInteraction {
	public:
		struct Make {
			virtual IBasicInteraction<T>* make(BasicActionInitInfo<T> initInfo) = 0;
			
			virtual ~Make() = default;
		};
		
		virtual void init(BasicActionInitInfo<T> initInfo);
		
		virtual IBasicInteraction<T>* copy() = 0;
	};
	
	using IBaseInteraction = IBasicInteraction<>;
}

#include "IInteraction.inl"
