#pragma once
#include "../event/button/empty/emptyEvent.hpp"
#include "../event/button/lambdaSimple/buttonEvent_LambdaSimple.hpp"

namespace ui {
	class IInteraction {
	public:
		enum class Priority {
			highest,
			medium,
			lowest,
		};
		
	public:
		virtual ~IInteraction() = default;
		
		virtual bool isBlocked() const;
		
		virtual Priority getPriority() const;
		
		virtual void start(sf::Vector2i mousePosition) = 0;
		
		virtual void update(sf::Vector2i mousePosition) = 0;
		
		virtual void finish(sf::Vector2i mousePosition) = 0;
		
		bool operator<(IInteraction& interaction) const;
		
		virtual IInteraction* copy() = 0;
	};
}
