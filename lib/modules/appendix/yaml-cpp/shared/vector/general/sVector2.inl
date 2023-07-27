//included into withVector2.hpp
#include <utility>

namespace ui {
	template<typename T>
	SVector2<T>::SVector2(const sf::Vector2<typename SVector2<T>::V>& vector) :
		x(std::make_shared<T>(vector.x)), y(std::make_shared<T>(vector.y)), setters() {
		x->addSetter([this](auto value) {
			set();
		});
		y->addSetter([this](auto value) {
			set();
		});
	}
	
	template<typename T>
	SVector2<T>::SVector2(std::shared_ptr<T> x, std::shared_ptr<T> y) :
		x(x), y(y), setters() {
			x->addSetter([this](auto value) {
				set();
			});
			y->addSetter([this](auto value) {
				set();
			});
	}
	
	template<typename T>
	void SVector2<T>::set() {
		for(const auto& setter: setters)
			setter(getValue());
	}
	
	template<typename T>
	void SVector2<T>::addSetter(const typename SVector2<T>::SetterFunc& setter) {
		setters.push_back(setter);
	}
	
	template<typename T>
	PIShared SVector2<T>::getXPtr() const {
		return std::dynamic_pointer_cast<IShared>(x);
	}
	
	template<typename T>
	void SVector2<T>::setXPtr(PIShared value) {
		x = std::dynamic_pointer_cast<T>(value);
		set();
	}
	
	template<typename T>
	PIShared SVector2<T>::getYPtr() const {
		return std::dynamic_pointer_cast<IShared>(y);
	}
	
	template<typename T>
	void SVector2<T>::setYPtr(PIShared value) {
		y = std::dynamic_pointer_cast<T>(value);
		set();
	}
	
	template<typename T>
	typename SVector2<T>::V SVector2<T>::getX() const {
		return x->getValue();
	}
	
	template<typename T>
	void SVector2<T>::setX(const typename SVector2<T>::V& value) {
		x->setValue(value);
		set();
	}
	
	template<typename T>
	typename SVector2<T>::V SVector2<T>::getY() const {
		return y->getValue();
	}
	
	template<typename T>
	void SVector2<T>::setY(const typename SVector2<T>::V& value) {
		y->setValue(value);
		set();
	}
	
	template<typename T>
	sf::Vector2<typename SVector2<T>::V> SVector2<T>::getValue() const {
		return {getX(), getY()};
	}
	
	template<typename T>
	void SVector2<T>::setValue(const sf::Vector2<typename SVector2<T>::V>& vector) {
		setX(vector.x);
		setY(vector.y);
		set();
	}
	
	template<typename T>
	void setRangeUpper(PSVec2<SRange<T>> value, sf::Vector2<T> upper) {
		std::dynamic_pointer_cast<SRange<T>>(value->getXPtr())->setUpper(upper.x);
		std::dynamic_pointer_cast<SRange<T>>(value->getYPtr())->setUpper(upper.y);
	}
	
	template<typename T>
	void setRangeLower(PSVec2<SRange<T>> value, sf::Vector2<T> lower) {
		std::dynamic_pointer_cast<SRange<T>>(value->getXPtr())->setLower(lower.x);
		std::dynamic_pointer_cast<SRange<T>>(value->getYPtr())->setLower(lower.y);
	}
	
	template<typename T>
	void setRangeBounds(PSVec2<SRange<T>> value, sf::Vector2<T> lower, sf::Vector2<T> upper) {
		std::dynamic_pointer_cast<SRange<T>>(value->getXPtr())->setBounds(lower.x, upper.x);
		std::dynamic_pointer_cast<SRange<T>>(value->getYPtr())->setBounds(lower.y, upper.y);
	}
	
	template<typename T>
	bool DecodePointer<SVector2<T> >::decodePointer(const YAML::Node& node, SVector2<T>*& withVector2) {
		if(node["x"] && node["y"]) {
			withVector2 = new SVector2<T>(getSValue<T>(node["x"]), getSValue<T>(node["y"]));
		} else {
			sf::Vector2<typename SVector2<T>::V> vector;
			
			if(node["vector"])
				node["vector"] >> vector;
			
			withVector2 = new SVector2<T>(vector);
		}
		return true;
	}
}