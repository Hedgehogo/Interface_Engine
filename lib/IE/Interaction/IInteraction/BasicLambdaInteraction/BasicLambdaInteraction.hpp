#pragma once

#include "../IInteraction.hpp"

namespace ie {
	template<typename T>
	class BasicLambdaInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicLambdaInteraction : public virtual IBasicInteraction<T> {
			void (* startPointing)(sf::Vector2i);
			void (* finishPointing)(sf::Vector2i);
			
			BasicLambdaInteraction(void (* startPointing)(sf::Vector2i mousePosition), void (* finishPointing)(sf::Vector2i mousePosition));
			
			ie::BasicLambdaInteraction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicLambdaInteraction : public virtual IBasicInteraction<T> {
	public:
		using Make = make_system::BasicLambdaInteraction<T>;
		
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
