namespace ie {
	template<typename T>
	SetSValueAction<T>::Make::Make(PISValue<T> value, T constant) :
		value(std::move(value)), constant(std::move(constant)) {
	}
	
	template<typename T>
	SetSValueAction<T>* SetSValueAction<T>::Make::make(ActionInitInfo init_info) {
		return new SetSValueAction<T>{std::move(*this), init_info};
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
	void SetSValueAction<T>::start_pressed() {}
	
	template<typename T>
	void SetSValueAction<T>::stop_pressed() {
		value->set_value(constant);
	}
	
	template<typename T>
	void SetSValueAction<T>::while_pressed() {}
	
	template<typename T>
	void SetSValueAction<T>::while_not_pressed() {}
	
	template<typename T>
	SetSValueAction<T>* SetSValueAction<T>::copy() {
		return new SetSValueAction<T>{*this};
	}
	
	template<typename T>
	bool DecodePointer<SetSValueAction<T> >::decode_pointer(const YAML::Node& node, SetSValueAction<T>*& set_s_value_action) {
		set_s_value_action = new SetSValueAction<T>{
			Buffer::get<ISValue<T> >(node["value"]),
			node["constant"].as<T>()
		};
		return true;
	}
}
