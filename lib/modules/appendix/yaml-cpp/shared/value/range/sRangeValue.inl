//included into sRangeValue.hpp

namespace ui {
	template <typename T>
	SRangeValue<T>::SRangeValue(T value) : SValue<T>(value) {}
	
	template <typename T>
	void SRangeValue<T>::setBounds(T upper, T bottom) {
		this->upper = std::min(this->upper, upper);
		this->bottom = std::max(this->bottom, bottom);
	}
	
	template <typename T>
	void SRangeValue<T>::setValue(const float &value) {
		this->value = std::min(std::max(value, bottom), upper);
		for(const auto &set: this->setters) set(this->value);
	}
	
	template <typename T>
	bool convertPointer(const YAML::Node &node, SRangeValue<T> *&sRangeValue) {
		sRangeValue = new SRangeValue<T>{convDef<T>(node["value"], {})};
		return true;
	}
}