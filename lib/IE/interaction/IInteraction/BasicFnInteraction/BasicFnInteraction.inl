namespace ie {
	namespace make_system {
		template<typename T>
		BasicFnInteraction<T>::BasicFnInteraction(FnType startFn, FnType finishFn) :
			startFn(std::move(startFn)), finishFn(std::move(finishFn)) {
		}
		
		template<typename T>
		ie::BasicFnInteraction<T>* BasicFnInteraction<T>::make(BasicActionInitInfo<T> initInfo) {
			return new ie::BasicFnInteraction<T>{std::move(*this), initInfo};
		}
	}
	
	template<typename T>
	BasicFnInteraction<T>::BasicFnInteraction(Make&& make, BasicActionInitInfo<T>) :
		startFn(std::move(make.startPointing)), finishFn(std::move(make.finishPointing)) {
	}
	
	template<typename T>
	BasicFnInteraction<T>::BasicFnInteraction(FnType startFn, FnType finishFn) :
		startFn(std::move(startFn)), finishFn(std::move(finishFn)) {
	}
	
	template<typename T>
	void BasicFnInteraction<T>::start(sf::Vector2i mousePosition) {
		startFn(mousePosition);
	}
	
	template<typename T>
	void BasicFnInteraction<T>::finish(sf::Vector2i mousePosition) {
		finishFn(mousePosition);
	}
}
