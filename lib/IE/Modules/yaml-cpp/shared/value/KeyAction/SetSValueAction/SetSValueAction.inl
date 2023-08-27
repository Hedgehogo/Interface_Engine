namespace ie {
	template<typename T>
	SetSValueAction<T>::SetSValueAction(const PISValue<T>& value, T variable) : value(value), variable(variable) {}
	
	template<typename T>
	void SetSValueAction<T>::startPressed() {}
	
	template<typename T>
	void SetSValueAction<T>::stopPressed() {
		value->setValue(variable);
	}
	
	template<typename T>
	void SetSValueAction<T>::whilePressed() {}
	
	template<typename T>
	void SetSValueAction<T>::whileNotPressed() {}
	
	template<typename T>
	SetSValueAction<T>* SetSValueAction<T>::copy() {
		return new SetSValueAction<T>{*this};
	}
	
	template<typename T>
	bool DecodePointer<SetSValueAction<T> >::decodePointer(const YAML::Node& node, SetSValueAction<T>*& setSValueAction) {
		setSValueAction = new SetSValueAction<T>{
			Buffer::get<ISValue<T> >(node["value"]),
			node["variable"].as<T>()
		};
		return true;
	}
}
