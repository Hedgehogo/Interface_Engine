#pragma once
#include "../event/button/empty/emptyEvent.h"
#include "../event/button/simple/buttonEventSimple.h"
#include "../event/button/lambdaSimple/buttonEvent_LambdaSimple.h"

namespace ui {
	enum class InteractionType {
		general,
		hidePanel,
		displayPanel
	};
	
	class IInteraction {
	private:
		bool blocked;
		
	public:
		explicit IInteraction(bool blocked = false);
		
		virtual ~IInteraction() = default;
		
		bool isBlocked() const;
		
		virtual InteractionType getType() const;
		
		virtual void start(sf::Vector2i mousePosition) = 0;
		
		virtual bool update(sf::Vector2i mousePosition) = 0;
		
		virtual void finish(sf::Vector2i mousePosition) = 0;
		
		virtual IInteraction* copy() = 0;
	};
}
