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
	
	template <typename T>
	WithValue<T> *WithValue<T>::createFromYaml(const YAML::Node &node) {
		T value;
		
		node["value"] >> value;
		
		return new WithValue<T>{value};
	}
}