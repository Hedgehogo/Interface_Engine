#pragma once

#include <functional>
#include <vector>
#include "../iAnimationVariable.hpp"
#include "../../convertToUse/iConvertToUse.hpp"

namespace ui {
	template<typename T>
	class AnimationVariable : public IAnimationVariable{
	public:
		using AnimationSetterFunc = std::function<void(T)>;

	protected:
		T value;
		IConvertToUse<T>* convertToUse;
		std::vector<AnimationSetterFunc> animationSetters;
		bool autoSet;

	public:
		AnimationVariable(T defaultValue, IConvertToUse <T>* convertToUse, bool autoSet = true);

		void addAnimationSetter(AnimationSetterFunc animationSetter);

		T get();

		void set(T& newValue);

		void valueFromAnimation(float newValue) override;

		T& operator*();

		T& operator->();

		AnimationVariable& operator=(const T& newValue);

		explicit operator T ();
	};
	typedef AnimationVariable<float> AnimationVariablef;
	typedef AnimationVariable<float> AVariablef;
	typedef AnimationVariable<int> AnimationVariablei;
	typedef AnimationVariable<int> AVariablei;

	template<typename T>
	bool convertPointer(const YAML::Node &node, AnimationVariable<T>*& animationUnit);
}

#include "animationVariable.inl"
