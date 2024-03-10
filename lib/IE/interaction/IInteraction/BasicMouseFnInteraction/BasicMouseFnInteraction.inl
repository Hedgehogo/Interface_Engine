//included into BasicMouseFnInteraction.hpp

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
		auto BasicMouseFnInteraction<T>::make(BasicActionInitInfo<T> init_info) -> ie::BasicMouseFnInteraction<T>* {
			return new ie::BasicMouseFnInteraction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicMouseFnInteraction<T>::BasicMouseFnInteraction(Make&& make, BasicActionInitInfo<T> init_info) :
		BasicFnInteraction<T>({std::move(make.start_fn), std::move(make.finish_fn)}, init_info),
		key_handler_(&init_info.key_handler),
		left_button_action_(make.left_button_action->make(init_info)),
		right_button_action_(make.right_button_action->make(init_info)) {
	}
	
	template<typename T>
	auto BasicMouseFnInteraction<T>::get_key_handler() -> KeyHandler& {
		return *key_handler_;
	}
	
	template<typename T>
	auto BasicMouseFnInteraction<T>::get_left_button_action() -> BasicKeyAction<T>& {
		return *left_button_action_;
	}
	
	template<typename T>
	auto BasicMouseFnInteraction<T>::get_left_button_action() const -> BasicKeyAction<T> const& {
		return *left_button_action_;
	}
	
	template<typename T>
	auto BasicMouseFnInteraction<T>::get_right_button_action() -> BasicKeyAction<T>& {
		return *right_button_action_;
	}
	
	template<typename T>
	auto BasicMouseFnInteraction<T>::get_right_button_action() const -> BasicKeyAction<T> const& {
		return *right_button_action_;
	}
}
