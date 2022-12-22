//included into BaseVariable.hpp

namespace ui {
	template<typename T>
	AnimationVariable<T>::AnimationVariable(T defaultValue, IConvertToUse <T>* convertToUse, bool autoSet) : value(defaultValue), convertToUse(convertToUse), autoSet(autoSet) {}

	template<typename T>
	void AnimationVariable<T>::addAnimationSetter(AnimationVariable::AnimationSetterFunc animationSetter) {
		animationSetters.push_back(animationSetter);
	}

	template<typename T>
	void AnimationVariable<T>::set(T &newValue) {
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

}
