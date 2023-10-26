#include <iostream>

namespace ie {
	namespace make_system {
		template<typename T>
		BasicMouseFnInteraction<T>::BasicMouseFnInteraction(
			BoxPtr<BasicKeyAction<T> >&& left_button_action,
			BoxPtr<BasicKeyAction<T> >&& right_button_action,
			FnType start_fn,
			FnType finish_fn
		) :
			BasicFnInteraction<T>(std::move(start_fn), std::move(finish_fn)),
			left_button_action(std::move(left_button_action)),
			right_button_action(std::move(right_button_action)) {
		}
		
		template<typename T>
		ie::BasicMouseFnInteraction<T>* BasicMouseFnInteraction<T>::make(BasicActionInitInfo<T> init_info) {
			return new ie::BasicMouseFnInteraction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicMouseFnInteraction<T>::BasicMouseFnInteraction(Make&& make, BasicActionInitInfo<T> init_info) :
		BasicFnInteraction<T>({std::move(make.start_fn), std::move(make.finish_fn)}, init_info),
		left_button_action_(make.left_button_action->make(init_info)),
		right_button_action_(make.right_button_action->make(init_info)) {
	}
	
	template<typename T>
	BasicMouseFnInteraction<T>::BasicMouseFnInteraction(
		BoxPtr<BasicKeyAction<T> >&& left_button_action,
		BoxPtr<BasicKeyAction<T> >&& right_button_action,
		FnType start_fn,
		FnType finish_fn
	) :
		BasicFnInteraction<T>(std::move(start_fn), std::move(finish_fn)),
		left_button_action_(std::move(left_button_action)),
		right_button_action_(std::move(right_button_action)) {
	}
	
	template<typename T>
	BasicKeyAction<T>& BasicMouseFnInteraction<T>::get_left_button_action() {
		return *left_button_action_;
	}
	
	template<typename T>
	const BasicKeyAction<T>& BasicMouseFnInteraction<T>::get_left_button_action() const {
		return *left_button_action_;
	}
	
	template<typename T>
	BasicKeyAction<T>& BasicMouseFnInteraction<T>::get_right_button_action() {
		return *right_button_action_;
	}
	
	template<typename T>
	const BasicKeyAction<T>& BasicMouseFnInteraction<T>::get_right_button_action() const {
		return *right_button_action_;
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
