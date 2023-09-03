#pragma once

#include "../IInteraction.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicLambdaInteraction : public virtual IBasicInteraction<T> {
	public:
		struct Make : public virtual IBasicInteraction<T>::Make {
			void (* startPointing)(sf::Vector2i);
			void (* finishPointing)(sf::Vector2i);
			
			Make(void (* startPointing)(sf::Vector2i mousePosition), void (* finishPointing)(sf::Vector2i mousePosition));
			
			BasicLambdaInteraction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
		
		BasicLambdaInteraction(Make&& make, BasicActionInitInfo<T> initInfo);
		
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
