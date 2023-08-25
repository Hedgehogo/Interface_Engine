namespace ui {
	template<typename T>
	BasicDoubleInteraction<T>::BasicDoubleInteraction(BoxPtr<IBasicInteraction<T> >&& first, BoxPtr<IBasicInteraction<T> >&& second) :
		first(std::move(first)), second(std::move(second)) {
	}
	
	template<typename T>
	void BasicDoubleInteraction<T>::setFirst(BoxPtr<IBasicInteraction<T> >&& first) {
		this->first = std::move(first);
	}
	
	template<typename T>
	void BasicDoubleInteraction<T>::setSecond(BoxPtr<IBasicInteraction<T> >&& second) {
		this->second = std::move(second);
	}
	
	template<typename T>
	IBasicInteraction<T>& BasicDoubleInteraction<T>::getFirst() {
		return *first;
	}
	
	template<typename T>
	const IBasicInteraction<T>& BasicDoubleInteraction<T>::getFirst() const {
		return *first;
	}
	
	template<typename T>
	IBasicInteraction<T>& BasicDoubleInteraction<T>::getSecond() {
		return *second;
	}
	
	template<typename T>
	const IBasicInteraction<T>& BasicDoubleInteraction<T>::getSecond() const {
		return *second;
	}
	
	template<typename T>
	void BasicDoubleInteraction<T>::start(sf::Vector2i mousePosition) {
		first->start(mousePosition);
		second->start(mousePosition);
	}
	
	template<typename T>
	void BasicDoubleInteraction<T>::update(sf::Vector2i mousePosition) {
		first->update(mousePosition);
		second->update(mousePosition);
	}
	
	template<typename T>
	void BasicDoubleInteraction<T>::finish(sf::Vector2i mousePosition) {
		second->finish(mousePosition);
		first->finish(mousePosition);
	}
	
	template<typename T>
	BasicDoubleInteraction<T>* BasicDoubleInteraction<T>::copy() {
		return new BasicDoubleInteraction<T>{*this};
	}
}
