//included into iWithVector2.hpp

namespace ui {
	template <typename T>
	void IWithVector2<T>::setX(const T &value) {
		setValue(sf::Vector2<T>{value, getY()});
	}
	
	template <typename T>
	void IWithVector2<T>::setY(const T &value) {
		setValue(sf::Vector2<T>{getX(), value});
	}
	
	template <typename T>
	sf::Vector2<T> IWithVector2<T>::getValue() const {
		return sf::Vector2<T>{getX(), getY()};
	}
	
	template <typename T>
	void IWithVector2<T>::setValue(const sf::Vector2<T> &vector) {
		setX(vector.x);
		setY(vector.y);
	}
	
	template <typename T>
	IWithVector2<T> *IWithVector2<T>::createFromYaml(const YAML::Node &node) {
		return nullptr;
	}
}