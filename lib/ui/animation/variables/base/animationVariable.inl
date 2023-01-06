//included into BaseVariable.hpp
#include "modules/appendix/yaml-animation/buffer.hpp"

namespace ui {
	template<typename T>
	AnimationVariable<T>::AnimationVariable(T defaultValue, IConvertToUse <T>* convertToUse, bool autoSet) : value(defaultValue), convertToUse(convertToUse), autoSet(autoSet) {}

	template<typename T>
	void AnimationVariable<T>::addAnimationSetter(AnimationVariable::AnimationSetterFunc animationSetter) {
		animationSetters.push_back(animationSetter);
	}

	template<typename T>
	void AnimationVariable<T>::set(const T &newValue) {
		value = newValue;
	}

	template<typename T>
	T AnimationVariable<T>::get() {
		return value;
	}

	template<typename T>
	void AnimationVariable<T>::valueFromAnimation(float newValue) {
		T convertValue = (*convertToUse)(newValue);
		if(autoSet) value = convertValue;

		for (const auto &animationSetter: animationSetters){
			animationSetter(convertValue);
		}
	}

	template<typename T>
	T& AnimationVariable<T>::operator*() {
		return value;
	}

	template<typename T>
	T& AnimationVariable<T>::operator->() {
		return value;
	}

	template<typename T>
	AnimationVariable<T>& AnimationVariable<T>::operator=(const T &newValue) {
		value = newValue;
		return *this;
	}

	template<typename T>
	AnimationVariable<T>::operator T() {
		return value;
	}

	template<typename T>
	bool convertPointer(const YAML::Node &node, AnimationVariable<T>*& animationVariable){
		animationVariable = new AnimationVariable<T>{
			node["var"].as<T>(),
			node["convert-to-use"].as<IConvertToUse<T> *>(),
			convDef(node["auto-set"], true)
		};

		if(node["name"]) animationVariablesBuffer[node["name"].as<std::string>()] = animationVariable;
		return true;
	}
}
