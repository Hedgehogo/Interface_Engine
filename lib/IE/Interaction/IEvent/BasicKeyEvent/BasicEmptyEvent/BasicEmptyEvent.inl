namespace ie {
	template<typename T>
	BasicEmptyEvent<T>::BasicEmptyEvent() : KeyEvent() {
	}
	
	template<typename T>
	void BasicEmptyEvent<T>::update(sf::Vector2i, bool) {
	}
	
	template<typename T>
	BasicEmptyEvent<T>* BasicEmptyEvent<T>::copy() {
		return new BasicEmptyEvent<T>{*this};
	}
}
