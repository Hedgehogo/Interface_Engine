//included into sValue_sf_Vector2.inl

namespace ui {
	template <typename T>
	SValue<sf::Vector2<T>>::SValue(const sf::Vector2<T> &value) : value(value) {}
	
	template <typename T>
	const T& SValue<sf::Vector2<T>>::getX() const {
		return value.x;
	}
	
	template <typename T>
	void SValue<sf::Vector2<T>>::setX(const T& value) {
		value.x = value;
	}
	
	template <typename T>
	const T& SValue<sf::Vector2<T>>::getY() const {
		return value.y;
	}
	
	template <typename T>
	void SValue<sf::Vector2<T>>::setY(const T& value) {
		value.y = value;
	}
	
	template <typename T>
	const sf::Vector2<T> &SValue<sf::Vector2<T>>::getValue() const {
		return value;
	}
	
	template <typename T>
	void SValue<sf::Vector2<T>>::setValue(const sf::Vector2<T>& value) {
		this->value = value;
	}
	
	template<typename T>
	bool convertPointer(const YAML::Node &node, SValue<sf::Vector2<T>> *&withValueVector2) {
		sf::Vector2<T> value{};
		
		if(node["value"]) node["value"] >> value;
		
		withValueVector2 = new SValue<sf::Vector2<T>>(value);
		return true;
	}
}