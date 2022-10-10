//included into withValue.hpp

namespace ui {
	template <typename T>
	SValue<T>::SValue(T value) : value(value) {}
	
	template <typename T>
	const T &SValue<T>::getValue() const {
		return value;
	}
	
	template <typename T>
	void SValue<T>::setValue(const T &value) {
		this->value = value;
	}
	
	template<typename T>
	bool convertPointer(const YAML::Node &node, SValue<T> *&sValue) {
		T value{};
		
		if(node["value"]) node["value"] >> value;
		
		sValue = new SValue<T>{value};
		return true;
	}
}