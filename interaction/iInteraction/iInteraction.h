#pragma once
#include "../event/button/empty/emptyEvent.h"
#include "../event/button/simple/buttonEventSimple.h"
#include "../event/button/lambdaSimple/buttonEvent_LambdaSimple.h"

namespace ui {
	class IInteraction {
	public:
		virtual ~IInteraction() = default;
		virtual void start(sf::Vector2i mousePosition) = 0;
		virtual bool update(sf::Vector2i mousePosition) = 0;
		virtual void finish(sf::Vector2i mousePosition) = 0;
	};
}
