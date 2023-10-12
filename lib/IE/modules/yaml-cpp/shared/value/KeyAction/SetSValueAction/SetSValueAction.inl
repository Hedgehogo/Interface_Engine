namespace ie {
	template<typename T>
	SetSValueAction<T>::Make::Make(PISValue<T> value, T constant) :
		value(std::move(value)), constant(std::move(constant)) {
	}
	
	template<typename T>
	SetSValueAction<T>* SetSValueAction<T>::Make::make(ActionInitInfo initInfo) {
		return new SetSValueAction<T>{std::move(*this), initInfo};
	}
	
	template<typename T>
	SetSValueAction<T>::SetSValueAction(Make&& make, ActionInitInfo) :
		value(std::move(make.value)), constant(std::move(make.value)) {
	}
	
	template<typename T>
	SetSValueAction<T>::SetSValueAction(PISValue<T> value, T constant) :
		value(std::move(value)), constant(std::move(constant)) {
	}
	
	template<typename T>
	void SetSValueAction<T>::startPressed() {}
	
	template<typename T>
	void SetSValueAction<T>::stopPressed() {
		value->setValue(constant);
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
			node["constant"].as<T>()
		};
		return true;
	}
}
