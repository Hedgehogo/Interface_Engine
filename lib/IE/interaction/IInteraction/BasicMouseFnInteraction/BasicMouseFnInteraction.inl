#include <iostream>

namespace ie {
	namespace make_system {
		template<typename T>
		BasicMouseFnInteraction<T>::BasicMouseFnInteraction(
			BoxPtr<BasicKeyAction<T> >&& leftButtonAction,
			BoxPtr<BasicKeyAction<T> >&& rightButtonAction,
			FnType startFn,
			FnType finishFn
		) :
			BasicFnInteraction<T>(std::move(startFn), std::move(finishFn)),
			leftButtonAction(std::move(leftButtonAction)),
			rightButtonAction(std::move(rightButtonAction)) {
		}
		
		template<typename T>
		ie::BasicMouseFnInteraction<T>* BasicMouseFnInteraction<T>::make(BasicActionInitInfo<T> initInfo) {
			return new ie::BasicMouseFnInteraction<T>{std::move(*this), initInfo};
		}
	}
	
	template<typename T>
	BasicMouseFnInteraction<T>::BasicMouseFnInteraction(Make&& make, BasicActionInitInfo<T> initInfo) :
		BasicFnInteraction<T>({std::move(make.startFn), std::move(make.finishFn)}, initInfo),
		leftButtonAction(make.leftButtonAction->make(initInfo)),
		rightButtonAction(make.rightButtonAction->make(initInfo)) {
	}
	
	template<typename T>
	BasicMouseFnInteraction<T>::BasicMouseFnInteraction(
		BoxPtr<BasicKeyAction<T> >&& leftButtonAction,
		BoxPtr<BasicKeyAction<T> >&& rightButtonAction,
		FnType startFn,
		FnType finishFn
	) :
		BasicFnInteraction<T>(std::move(startFn), std::move(finishFn)),
		leftButtonAction(std::move(leftButtonAction)),
		rightButtonAction(std::move(rightButtonAction)) {
	}
	
	template<typename T>
	BasicKeyAction<T>& BasicMouseFnInteraction<T>::getLeftButtonAction() {
		return *leftButtonAction;
	}
	
	template<typename T>
	const BasicKeyAction<T>& BasicMouseFnInteraction<T>::getLeftButtonAction() const {
		return *leftButtonAction;
	}
	
	template<typename T>
	BasicKeyAction<T>& BasicMouseFnInteraction<T>::getRightButtonAction() {
		return *rightButtonAction;
	}
	
	template<typename T>
	const BasicKeyAction<T>& BasicMouseFnInteraction<T>::getRightButtonAction() const {
		return *rightButtonAction;
	}
	
	template<typename T>
	BasicMouseFnInteraction<T>* BasicMouseFnInteraction<T>::copy() {
		return new BasicMouseFnInteraction<T>{*this};
	}
	
	template<typename T>
	BasicMouseFnInteraction<T> BasicMouseFnInteraction<T>::debug{
		make_box_ptr<BasicKeyAction<T>, BasicFnKeyAction<T> >(
			[](sf::Vector2i) {
				std::cout << "sl";
			},
			[](sf::Vector2i) {
				std::cout << "wl";
			},
			[](sf::Vector2i) {
				std::cout << "sl";
			},
			[](sf::Vector2i) {
				std::cout << "nl";
			}
		),
		make_box_ptr<BasicKeyAction<T>, BasicFnKeyAction<T> >(
			[](sf::Vector2i) {
				std::cout << "sr" << std::endl;
			},
			[](sf::Vector2i) {
				std::cout << "wr" << std::endl;
			},
			[](sf::Vector2i) {
				std::cout << "sr" << std::endl;
			},
			[](sf::Vector2i) {
				std::cout << "nr" << std::endl;
			}
		),
		[](sf::Vector2i) {
			std::cout << "sp" << std::endl;
		},
		[](sf::Vector2i) {
			std::cout << "fp" << std::endl;
		}
	};
}
