namespace ie {
	template<typename T>
	SConvertRange<T>::SConvertRange(PSRange<T> sRangeValue, T upper, T lower) : sRangeValue(sRangeValue) {
		sRangeValue->addSetter([=](const T& value){
			this->setValue(value * ((upper - lower) / (sRangeValue->getUpper() - sRangeValue->getLower())));
		});
	}
	
	template<typename T>
	bool DecodePointer<SConvertRange<T> >::decodePointer(const YAML::Node& node, SConvertRange<T>*& sConvertRange) {
		sConvertRange = new SConvertRange<T>{
			Buffer::get<SRangeValue<T> >(node["value"]),
			node["upper"].as<T>(),
			node["lower"].as<T>()
		};
		return true;
	}
}