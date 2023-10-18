//included into with_value.hpp

namespace ie {
	template<typename T>
	SValue<T>::SValue(T value) : value(value), setters() {
	}
	
	template<typename T>
	void SValue<T>::add_setter(const typename ISValue<T>::SetterFunc& setter) {
		setters.push_back(setter);
	}
	
	template<typename T>
	const T& SValue<T>::get_value() const {
		return value;
	}
	
	template<typename T>
	void SValue<T>::set_value(const T& value) {
		this->value = value;
		for(const auto& set: setters)
			set(value);
	}
	
	template<typename T>
	bool DecodePointer<SValue<T> >::decode_pointer(const YAML::Node& node, SValue<T>*& sValue) {
		T value{};
		
		if(node["value"])
			node["value"] >> value;
		
		sValue = new SValue<T>{value};
		return true;
	}
}