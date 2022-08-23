//included into withValue_sf_Vector2.inl

namespace ui {
	template <typename T>
	WithValue<sf::Vector2<T>>::WithValue(const sf::Vector2<T> &value) : value(value) {}
	
	template <typename T>
	const T& WithValue<sf::Vector2<T>>::getX() const {
		return value.x;
	}
	
	template <typename T>
	void WithValue<sf::Vector2<T>>::setX(const T& value) {
		value.x = value;
	}
	
	template <typename T>
	const T& WithValue<sf::Vector2<T>>::getY() const {
		return value.y;
	}
	
	template <typename T>
	void WithValue<sf::Vector2<T>>::setY(const T& value) {
		value.y = value;
	}
	
	template <typename T>
	const sf::Vector2<T> &WithValue<sf::Vector2<T>>::getValue() const {
		return value;
	}
	
	template <typename T>
	void WithValue<sf::Vector2<T>>::setValue(const sf::Vector2<T>& value) {
		this->value = value;
	}
	
	template <typename T>
	WithValue<sf::Vector2<T>> *WithValue<sf::Vector2<T>>::createFromYaml(const YAML::Node &node) {
		sf::Vector2<T> value{};
		
		if(node["value"]) node["value"] >> value;
		
		return new WithValue<sf::Vector2<T>>(value);
	}
}