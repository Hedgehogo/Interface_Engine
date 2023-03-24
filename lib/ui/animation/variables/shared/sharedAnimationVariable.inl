//included into sharedAnimationVariable.hpp

namespace ui {
	template<typename T>
	SharedAnimationVariable<T>::SharedAnimationVariable(std::shared_ptr<ISValue<T>> value, IConvertToUse <T> *convertToUse) : value(value), convertToUse(convertToUse) {}

	template<typename T>
	void SharedAnimationVariable<T>::valueFromAnimation(float newValue) {
		value->setValue((*convertToUse)(newValue));
	}

	template<typename T>
	bool convertPointer(const YAML::Node &node, SharedAnimationVariable<T>*& sharedAnimationVariable){
		sharedAnimationVariable = new SharedAnimationVariable<T>{
			Buffer::get<ISValue<T>>(node["value"]),
			node["convert-to-use"].as<IConvertToUse<T>*>()
		};
		return true;
	}
}