#pragma once

#include "../BasicLambdaInteraction/BasicLambdaInteraction.hpp"
#include "../IBasicMouseInteraction/IBasicMouseInteraction.hpp"

namespace ie {
	template<typename T>
	class BasicMouseLambdaInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicMouseLambdaInteraction : public BasicLambdaInteraction<T>, public virtual IBasicMouseInteraction<T> {
			BoxPtr<typename ie::BasicKeyAction<T>::Make> leftButtonAction;
			BoxPtr<typename ie::BasicKeyAction<T>::Make> rightButtonAction;
			
			BasicMouseLambdaInteraction(
				BoxPtr<typename ie::BasicKeyAction<T>::Make>&& leftButtonAction,
				BoxPtr<typename ie::BasicKeyAction<T>::Make>&& rightButtonAction,
				void (* startPointing)(sf::Vector2i mousePosition),
				void (* finishPointing)(sf::Vector2i mousePosition)
			);
			
			ie::BasicMouseLambdaInteraction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicMouseLambdaInteraction : public BasicLambdaInteraction<T>, public virtual IBasicMouseInteraction<T> {
	public:
		using Make = make_system::BasicMouseLambdaInteraction<T>;
		
		BasicMouseLambdaInteraction(Make&& make, BasicActionInitInfo<T> initInfo);
		
		BasicMouseLambdaInteraction(
			BoxPtr<BasicKeyAction<T> >&& leftButtonAction,
			BoxPtr<BasicKeyAction<T> >&& rightButtonAction,
			void (* startPointing)(sf::Vector2i mousePosition),
			void (* finishPointing)(sf::Vector2i mousePosition)
		);
		
		BasicKeyAction<T>& getLeftButtonAction() override;
		
		const BasicKeyAction<T>& getLeftButtonAction() const override;
		
		BasicKeyAction<T>& getRightButtonAction() override;
		
		const BasicKeyAction<T>& getRightButtonAction() const override;
		
		BasicMouseLambdaInteraction<T>* copy() override;
	
		static BasicMouseLambdaInteraction debug;
		
	protected:
		BoxPtr<BasicKeyAction<T> > leftButtonAction;
		BoxPtr<BasicKeyAction<T> > rightButtonAction;
	};
	
	using MouseLambdaInteraction = BasicMouseLambdaInteraction<>;
}

#include "BasicMouseLambdaInteraction.inl"
