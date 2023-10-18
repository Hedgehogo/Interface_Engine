namespace ie {
	template<typename T>
	SConvertRange<T>::SConvertRange(PSRange<T> sRange_value, T upper, T lower) : sRange_value(sRange_value) {
		sRange_value->add_setter([=](const T& value){
			this->set_value(value * ((upper - lower) / (sRange_value->get_upper() - sRange_value->get_lower())));
		});
	}
	
	template<typename T>
	bool DecodePointer<SConvertRange<T> >::decode_pointer(const YAML::Node& node, SConvertRange<T>*& sConvert_range) {
		sConvert_range = new SConvertRange<T>{
			Buffer::get<SRangeValue<T> >(node["value"]),
			node["upper"].as<T>(),
			node["lower"].as<T>()
		};
		return true;
	}
}