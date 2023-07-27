namespace ui {
	template<typename T>
	SetSValueEvent<T>::SetSValueEvent(const PISValue<T>& value, T variable) : value(value), variable(variable) {}
	
	template<typename T>
	void SetSValueEvent<T>::startPressed() {}
	
	template<typename T>
	void SetSValueEvent<T>::stopPressed() {
		value->setValue(variable);
	}
	
	template<typename T>
	void SetSValueEvent<T>::whilePressed() {}
	
	template<typename T>
	void SetSValueEvent<T>::whileNotPressed() {}
	
	template<typename T>
	SetSValueEvent<T>* SetSValueEvent<T>::copy() {
		return new SetSValueEvent<T>{value, variable};
	}
	
	template<typename T>
	bool DecodePointer<SetSValueEvent<T>>::decodePointer(const YAML::Node& node, SetSValueEvent<T>*& setSValueEvent) {
		setSValueEvent = new SetSValueEvent<T>{
			Buffer::get<ISValue<T> >(node["value"]),
			node["variable"].as<T>()
		};
		return true;
	}
}
