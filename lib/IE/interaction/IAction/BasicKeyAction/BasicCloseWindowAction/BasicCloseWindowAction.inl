#include "IE/window/Window/Window.hpp"

namespace ie {
	namespace make_system {
		template<typename T>
		auto BasicCloseWindowAction<T>::make(BasicActionInitInfo<T> init_info) -> ie::BasicCloseWindowAction<T>* {
			return new ie::BasicCloseWindowAction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicCloseWindowAction<T>::BasicCloseWindowAction(Make&&, BasicActionInitInfo<T> init_info) :
		window_(&init_info.window) {
	}
	
	template<typename T>
	auto BasicCloseWindowAction<T>::start_pressed() -> void {
	}
	
	template<typename T>
	auto BasicCloseWindowAction<T>::stop_pressed() -> void {
		if(window_->isOpen())
			window_->close();
	}
	
	template<typename T>
	auto BasicCloseWindowAction<T>::while_pressed() -> void {
	}
	
	template<typename T>
	auto BasicCloseWindowAction<T>::while_not_pressed() -> void {
	}
}

template<typename T>
auto ieml::Decode<char, ie::BasicCloseWindowAction<T> >::decode(ieml::Node const&) -> orl::Option<ie::BasicCloseWindowAction<T> > {
	return ie::BasicCloseWindowAction<T>{};
}
