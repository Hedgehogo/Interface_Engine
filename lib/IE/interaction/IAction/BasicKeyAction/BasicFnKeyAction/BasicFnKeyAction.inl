namespace ie {
	namespace make_system {
		template<typename T>
		BasicFnKeyAction<T>::BasicFnKeyAction(FnType startPressedFn, FnType whilePressedFn, FnType stopPressedFn, FnType whileNotPressedFn) :
			startPressedFn(std::move(startPressedFn)), 
			whilePressedFn(std::move(whilePressedFn)), 
			stopPressedFn(std::move(stopPressedFn)), 
			whileNotPressedFn(std::move(whileNotPressedFn)) {
		}
		
		template<typename T>
		ie::BasicFnKeyAction<T>* BasicFnKeyAction<T>::make(BasicActionInitInfo<T> initInfo) {
			return new ie::BasicFnKeyAction<T>{std::move(*this), initInfo};
		}
	}
	
	template<typename T>
	BasicFnKeyAction<T>::BasicFnKeyAction(Make&& make, BasicActionInitInfo<T>) :
		startPressedFn(std::move(make.startPressedFn)),
		whilePressedFn(std::move(make.whilePressedFn)),
		stopPressedFn(std::move(make.stopPressedFn)),
		whileNotPressedFn(std::move(make.whileNotPressedFn)) {
	}
	
	template<typename T>
	BasicFnKeyAction<T>::BasicFnKeyAction(FnType startPressedFn, FnType whilePressedFn, FnType stopPressedFn, FnType whileNotPressedFn) :
		startPressedFn(std::move(startPressedFn)),
		whilePressedFn(std::move(whilePressedFn)),
		stopPressedFn(std::move(stopPressedFn)),
		whileNotPressedFn(std::move(whileNotPressedFn)) {
	}
	
	template<typename T>
	void BasicFnKeyAction<T>::startPressed() {
		startPressedFn(this->mousePosition);
	}
	
	template<typename T>
	void BasicFnKeyAction<T>::stopPressed() {
		stopPressedFn(this->mousePosition);
	}
	
	template<typename T>
	void BasicFnKeyAction<T>::whilePressed() {
		whilePressedFn(this->mousePosition);
	}
	
	template<typename T>
	void BasicFnKeyAction<T>::whileNotPressed() {
		whileNotPressedFn(this->mousePosition);
	}
	
	template<typename T>
	BasicFnKeyAction<T>* BasicFnKeyAction<T>::copy() {
		return new BasicFnKeyAction<T>{*this};
	}
}

