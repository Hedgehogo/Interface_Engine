//included into withVector2.hpp
#include <utility>

namespace ui {
	template <typename T>
	WithVector2<T>::WithVector2(const sf::Vector2<typename WithVector2<T>::V> &vector) : x(std::make_shared<T>(vector.x)), y(std::make_shared<T>(vector.y)) {}
	
	template <typename T>
	WithVector2<T>::WithVector2(std::shared_ptr<T> x, std::shared_ptr<T> y) :
		x(x), y(y) {}
	
	template <typename T>
	std::shared_ptr<IWith> WithVector2<T>::getXPtr() const {
		return std::dynamic_pointer_cast<IWith>(x);
	}
	
	template <typename T>
	void WithVector2<T>::setXPtr(std::shared_ptr<IWith> value) {
		x = std::dynamic_pointer_cast<T>(value);
	}
	
	template <typename T>
	std::shared_ptr<IWith> WithVector2<T>::getYPtr() const {
		return std::dynamic_pointer_cast<IWith>(y);
	}
	
	template <typename T>
	void WithVector2<T>::setYPtr(std::shared_ptr<IWith> value) {
		y = std::dynamic_pointer_cast<T>(value);
	}
	
	template <typename T>
	typename WithVector2<T>::V WithVector2<T>::getX() const {
		return x->getValue();
	}
	
	template <typename T>
	void WithVector2<T>::setX(const typename WithVector2<T>::V &value) {
		x->setValue(value);
	}
	
	template <typename T>
	typename WithVector2<T>::V WithVector2<T>::getY() const {
		return y->getValue();
	}
	
	template <typename T>
	void WithVector2<T>::setY(const typename WithVector2<T>::V &value) {
		y->setValue(value);
	}
	
	template <typename T>
	sf::Vector2<typename WithVector2<T>::V> WithVector2<T>::getValue() const {
		return {getX(), getY()};
	}
	
	template <typename T>
	void WithVector2<T>::setValue(const sf::Vector2<typename WithVector2<T>::V> &vector) {
		setX(vector.x);
		setY(vector.y);
	}
}