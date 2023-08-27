namespace ie {
	template<typename T>
	BasicEmptyAction<T>::BasicEmptyAction() : KeyAction() {
	}
	
	template<typename T>
	void BasicEmptyAction<T>::update(sf::Vector2i, bool) {
	}
	
	template<typename T>
	BasicEmptyAction<T>* BasicEmptyAction<T>::copy() {
		return new BasicEmptyAction<T>{*this};
	}
}
