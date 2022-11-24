//included into sRangeValue.hpp

namespace ui {
	template <typename T>
	SRangeValue<T>::SRangeValue(T value) : SValue<T>(value), upper(std::numeric_limits<float>::max()), lower(std::numeric_limits<float>::min()) {}
	
	template <typename T>
	T SRangeValue<T>::getUpper() { return upper; }
	
	template <typename T>
	T SRangeValue<T>::getLower() { return lower; }
	
	template <typename T>
	void SRangeValue<T>::setUpper(const T &upper) { this->upper = std::min(this->upper, upper); }
	
	template <typename T>
	void SRangeValue<T>::setLower(const T &lower) { this->lower = std::max(this->lower, lower); }
	
	template <typename T>
	void SRangeValue<T>::setBounds(T lower, T upper) {
		setUpper(upper);
		setLower(lower);
	}
	
	template <typename T>
	void SRangeValue<T>::setValue(const float &value) {
		this->value = std::clamp(value, lower, upper);
		for(const auto &set: this->setters) set(this->value);
	}
	
	template <typename T>
	bool convertPointer(const YAML::Node &node, SRangeValue<T> *&sRangeValue) {
		sRangeValue = new SRangeValue<T>{convDef<T>(node["value"], {})};
		return true;
	}
}