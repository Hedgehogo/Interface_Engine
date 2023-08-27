#include "IE/Window/Window.hpp"

namespace ie {
	template<typename T>
	BasicCloseWindowEvent<T>::BasicCloseWindowEvent() : window{nullptr}{
	}
	
	template<typename T>
	void BasicCloseWindowEvent<T>::startPressed() {
	}
	
	template<typename T>
	void BasicCloseWindowEvent<T>::stopPressed() {
		window->close();
	}
	
	template<typename T>
	void BasicCloseWindowEvent<T>::whilePressed() {
	}
	
	template<typename T>
	void BasicCloseWindowEvent<T>::whileNotPressed() {
	}
	
	template<typename T>
	void BasicCloseWindowEvent<T>::init(BasicInteractionInitInfo<T> initInfo) {
		BasicBaseKeyEvent<T>::init(initInfo);
		window = &initInfo.window;
	}
	
	template<typename T>
	BasicCloseWindowEvent<T>* BasicCloseWindowEvent<T>::copy() {
		return new BasicCloseWindowEvent<T>{*this};
	}
	
	template<typename T>
	bool DecodePointer<BasicCloseWindowEvent<T> >::decodePointer(const YAML::Node&, BasicCloseWindowEvent<T>*& closeWindowEvent) {
		closeWindowEvent = new BasicCloseWindowEvent<T>{};
		return true;
	}
}