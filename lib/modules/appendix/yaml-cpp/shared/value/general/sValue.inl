//included into withValue.hpp

namespace ui {
	template<typename T>
	SValue<T>::SValue(T value) : value(value), setters() {
	}
	
	template<typename T>
	void SValue<T>::addSetter(const typename ISValue<T>::SetterFunc& setter) {
		setters.push_back(setter);
	}
	
	template<typename T>
	const T& SValue<T>::getValue() const {
		return value;
	}
	
	template<typename T>
	void SValue<T>::setValue(const T& value) {
		this->value = value;
		for(const auto& set: setters)
			set(value);
	}
	
	template<typename T>
	bool convertPointer(const YAML::Node &node, SValue<T> *&sValue) {
		T value{};
		
		if(node["value"])
			node["value"] >> value;
		
		sValue = new SValue<T>{value};
		return true;
	}
	
	template<typename T>
	bool DecodePointer<SValue<T>>::decodePointer(const YAML::Node &node, SValue<T> *&sValue) {
		T value{};
		
		if(node["value"])
			node["value"] >> value;
		
		sValue = new SValue<T>{value};
		return true;
	}
}