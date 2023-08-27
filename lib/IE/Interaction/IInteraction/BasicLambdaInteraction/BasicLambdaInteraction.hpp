#pragma once

#include "../IInteraction.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicLambdaInteraction : public virtual IBasicInteraction<T> {
	public:
		BasicLambdaInteraction(void (* startPointing)(sf::Vector2i mousePosition), void (* finishPointing)(sf::Vector2i mousePosition));
		
		void start(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
	
	protected:
		void (* startPointing)(sf::Vector2i mousePosition);
		void (* finishPointing)(sf::Vector2i mousePosition);
	};
	
	using LambdaInteraction = BasicLambdaInteraction<>;
}

#include "BasicLambdaInteraction.inl"
