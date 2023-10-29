namespace ie {
	template<typename T>
	SConvertRange<T>::SConvertRange(PSRange<T> value, T upper, T lower) : value_(value) {
		value->add_setter([=](const T& value){
			this->set_value(value * ((upper - lower) / (value_->get_upper() - value_->get_lower())));
		});
	}
	
	/*old_yaml_decode_pointer_impl
	template<typename T>
	bool DecodePointer<SConvertRange<T> >::decode_pointer(const YAML::Node& node, SConvertRange<T>*& sConvert_range) {
		sConvert_range = new SConvertRange<T>{
			Buffer::get<SRangeValue<T> >(node["value"]),
			node["upper"].as<T>(),
			node["lower"].as<T>()
		};
		return true;

	}
	*/
}