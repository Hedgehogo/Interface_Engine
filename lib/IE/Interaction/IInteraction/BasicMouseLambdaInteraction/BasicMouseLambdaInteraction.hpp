#pragma once

#include "../BasicLambdaInteraction/BasicLambdaInteraction.hpp"
#include "../IBasicMouseInteraction/IBasicMouseInteraction.hpp"

namespace ui {
	template<typename T = std::monostate>
	class BasicMouseLambdaInteraction : public BasicLambdaInteraction<T>, public IBasicMouseInteraction<T> {
	public:
		BasicMouseLambdaInteraction(
			BoxPtr<BasicKeyEvent<T> >&& leftButtonEvent,
			BoxPtr<BasicKeyEvent<T> >&& rightButtonEvent,
			void (* startPointing)(sf::Vector2i mousePosition),
			void (* finishPointing)(sf::Vector2i mousePosition)
		);
		
		BasicKeyEvent<T>& getLeftButtonEvent() override;
		
		const BasicKeyEvent<T>& getLeftButtonEvent() const override;
		
		BasicKeyEvent<T>& getRightButtonEvent() override;
		
		const BasicKeyEvent<T>& getRightButtonEvent() const override;
		
		BasicMouseLambdaInteraction<T>* copy() override;
	
		static BasicMouseLambdaInteraction debug;
		
	protected:
		BoxPtr<BasicKeyEvent<T> > leftButtonEvent;
		BoxPtr<BasicKeyEvent<T> > rightButtonEvent;
	};
	
	using MouseLambdaInteraction = BasicMouseLambdaInteraction<>;
}

#include "BasicMouseLambdaInteraction.inl"
