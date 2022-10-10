//included into withValue.hpp

namespace ui {
	template <typename T>
	WithValue<T>::WithValue(T value) : value(value) {}
	
	template <typename T>
	const T &WithValue<T>::getValue() const {
		return value;
	}
	
	template <typename T>
	void WithValue<T>::setValue(const T &value) {
		this->value = value;
	}
	
	template<typename T>
	bool convertPointer(const YAML::Node &node, WithValue<T> *&withValue) {
		T value{};
		
		if(node["value"]) node["value"] >> value;
		
		withValue = new WithValue<T>{value};
		return true;
	}
}