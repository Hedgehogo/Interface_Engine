#pragma once
#include "../event/button/empty/emptyEvent.h"
#include "../event/button/simple/buttonEventSimple.h"
#include "../event/button/lambdaSimple/buttonEvent_LambdaSimple.h"

namespace ui {
	class IInteraction {
	private:
		bool blocked;
		
	public:
		enum class Priority {
			highest,
			medium,
			lowest,
		};
		
		explicit IInteraction(bool blocked = false);
		
		virtual ~IInteraction() = default;
		
		bool isBlocked() const;
		
		virtual Priority getPriority() const;
		
		virtual void start(sf::Vector2i mousePosition) = 0;
		
		virtual bool update(sf::Vector2i mousePosition) = 0;
		
		virtual void finish(sf::Vector2i mousePosition) = 0;
		
		bool operator<(IInteraction& interaction);
		
		virtual IInteraction* copy() = 0;
	};
}
