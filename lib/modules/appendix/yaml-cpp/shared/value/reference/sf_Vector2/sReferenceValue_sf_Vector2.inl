//included into withReferenceValue_sf_Vector2.inl

namespace ui {
	template <typename T>
	WithReferenceValue<sf::Vector2<T>>::WithReferenceValue(sf::Vector2<T> &valueReference) : valueReference(&valueReference) {}
	
	template <typename T>
	const T& SReferenceValue<sf::Vector2<T>>::getX() const {
		return valueReference->x;
	}
	
	template <typename T>
	void SReferenceValue<sf::Vector2<T>>::setX(const T& value) {
		valueReference->x = valueReference;
	}
	
	template <typename T>
	const T& SReferenceValue<sf::Vector2<T>>::getY() const {
		return valueReference->y;
	}
	
	template <typename T>
	void SReferenceValue<sf::Vector2<T>>::setY(const T& value) {
		valueReference->y = valueReference;
	}
	
	template <typename T>
	const sf::Vector2<T> &WithReferenceValue<sf::Vector2<T>>::getValue() const {
		return *valueReference;
	}
	
	template <typename T>
	void SReferenceValue<sf::Vector2<T>>::setValue(const sf::Vector2<T>& value) {
		*this->valueReference = valueReference;
	}
	
	template <typename T>
	void SReferenceValue<sf::Vector2<T>>::setReference(T& valueReference) {
		this->valueReference = &valueReference;
	}
}