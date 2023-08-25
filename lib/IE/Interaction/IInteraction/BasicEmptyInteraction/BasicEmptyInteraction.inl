namespace ui {
	template<typename T>
	BasicEmptyInteraction<T>::BasicEmptyInteraction() {
	}
	
	template<typename T>
	void BasicEmptyInteraction<T>::start(sf::Vector2i) {
	}
	
	template<typename T>
	void BasicEmptyInteraction<T>::update(sf::Vector2i) {
	}
	
	template<typename T>
	void BasicEmptyInteraction<T>::finish(sf::Vector2i) {
	}
	
	template<typename T>
	BasicEmptyInteraction<T>* BasicEmptyInteraction<T>::copy() {
		return new BasicEmptyInteraction<T>{};
	}
	
	template<typename T>
	bool DecodePointer<BasicEmptyInteraction<T> >::decodePointer(const YAML::Node&, BasicEmptyInteraction<T>*& emptyInteraction) {
		{
			emptyInteraction = new BasicEmptyInteraction<T>{};
			return true;
		}
	}
}
