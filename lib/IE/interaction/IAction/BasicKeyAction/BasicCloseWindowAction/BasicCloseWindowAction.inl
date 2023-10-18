#include "IE/window/Window/Window.hpp"

namespace ie {
	namespace make_system {
		template<typename T>
		ie::BasicCloseWindowAction<T>* BasicCloseWindowAction<T>::make(BasicActionInitInfo<T> init_info) {
			return new ie::BasicCloseWindowAction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicCloseWindowAction<T>::BasicCloseWindowAction(Make&&, BasicActionInitInfo<T> init_info) :
		window(&init_info.window) {
	}
	
	template<typename T>
	BasicCloseWindowAction<T>::BasicCloseWindowAction() : window{nullptr}{
	}
	
	template<typename T>
	void BasicCloseWindowAction<T>::start_pressed() {
	}
	
	template<typename T>
	void BasicCloseWindowAction<T>::stop_pressed() {
		if(window->isOpen())
			window->close();
	}
	
	template<typename T>
	void BasicCloseWindowAction<T>::while_pressed() {
	}
	
	template<typename T>
	void BasicCloseWindowAction<T>::while_not_pressed() {
	}
	
	template<typename T>
	void BasicCloseWindowAction<T>::init(BasicActionInitInfo<T> init_info) {
		BasicBaseKeyAction<T>::init(init_info);
		window = &init_info.window;
	}
	
	template<typename T>
	BasicCloseWindowAction<T>* BasicCloseWindowAction<T>::copy() {
		return new BasicCloseWindowAction<T>{*this};
	}
	
	template<typename T>
	bool DecodePointer<BasicCloseWindowAction<T> >::decode_pointer(const YAML::Node&, BasicCloseWindowAction<T>*& close_window_action) {
		close_window_action = new BasicCloseWindowAction<T>{};
		return true;
	}
}