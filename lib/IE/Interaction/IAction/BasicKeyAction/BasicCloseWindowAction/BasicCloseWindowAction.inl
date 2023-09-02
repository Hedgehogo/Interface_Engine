#include "IE/Window/Window.hpp"

namespace ie {
	template<typename T>
	BasicCloseWindowAction<T>* BasicCloseWindowAction<T>::Make::make(BasicActionInitInfo<T> initInfo) {
		return new BasicCloseWindowAction<T>{std::move(*this), initInfo};
	}
	
	template<typename T>
	BasicCloseWindowAction<T>::BasicCloseWindowAction(Make&&, BasicActionInitInfo<T> initInfo) :
		window(&initInfo.window) {
	}
	
	template<typename T>
	BasicCloseWindowAction<T>::BasicCloseWindowAction() : window{nullptr}{
	}
	
	template<typename T>
	void BasicCloseWindowAction<T>::startPressed() {
	}
	
	template<typename T>
	void BasicCloseWindowAction<T>::stopPressed() {
		if(window->isOpen())
			window->close();
	}
	
	template<typename T>
	void BasicCloseWindowAction<T>::whilePressed() {
	}
	
	template<typename T>
	void BasicCloseWindowAction<T>::whileNotPressed() {
	}
	
	template<typename T>
	void BasicCloseWindowAction<T>::init(BasicActionInitInfo<T> initInfo) {
		BasicBaseKeyAction<T>::init(initInfo);
		window = &initInfo.window;
	}
	
	template<typename T>
	BasicCloseWindowAction<T>* BasicCloseWindowAction<T>::copy() {
		return new BasicCloseWindowAction<T>{*this};
	}
	
	template<typename T>
	bool DecodePointer<BasicCloseWindowAction<T> >::decodePointer(const YAML::Node&, BasicCloseWindowAction<T>*& closeWindowAction) {
		closeWindowAction = new BasicCloseWindowAction<T>{};
		return true;
	}
}