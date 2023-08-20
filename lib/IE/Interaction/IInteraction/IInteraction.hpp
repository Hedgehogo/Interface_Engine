#pragma once

#include "../IEvent/KeyEvent/EmptyEvent/EmptyEvent.hpp"
#include "../IEvent/KeyEvent/LambdaKeyEvent/LambdaKeyEvent.hpp"
#include "../InteractionInitInfo/InteractionInitInfo.hpp"
#include <Box_Ptr/boxPtr.hpp>

namespace ui {
	using namespace bp;
	
	class InteractionManager;
	
	class IInteraction {
	public:
		enum class Priority {
			highest,
			medium,
			lowest,
		};
	
		virtual ~IInteraction() = default;
		
		virtual void init(InteractionInitInfo);
		
		virtual bool isBlocked() const;
		
		virtual Priority getPriority() const;
		
		virtual void start(sf::Vector2i mousePosition) = 0;
		
		virtual void update(sf::Vector2i mousePosition) = 0;
		
		virtual void finish(sf::Vector2i mousePosition) = 0;
		
		bool operator<(IInteraction& interaction) const;
		
		virtual IInteraction* copy() = 0;
	};
}
