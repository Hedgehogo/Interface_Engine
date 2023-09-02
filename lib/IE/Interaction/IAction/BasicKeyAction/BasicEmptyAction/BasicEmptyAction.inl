namespace ie {
	template<typename T>
	BasicEmptyAction<T>* BasicEmptyAction<T>::Make::make(BasicActionInitInfo<T> initInfo) {
		return new BasicEmptyAction<T>{std::move(*this), initInfo};
	}
	
	template<typename T>
	BasicEmptyAction<T>::BasicEmptyAction(Make&&, BasicActionInitInfo<T>) {
	}
	
	template<typename T>
	BasicEmptyAction<T>::BasicEmptyAction() {
	}
	
	template<typename T>
	void BasicEmptyAction<T>::update(sf::Vector2i, bool) {
	}
	
	template<typename T>
	BasicEmptyAction<T>* BasicEmptyAction<T>::copy() {
		return new BasicEmptyAction<T>{*this};
	}
}
