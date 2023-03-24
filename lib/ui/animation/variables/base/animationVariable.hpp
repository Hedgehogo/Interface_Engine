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

		void set(const T &newValue);

		void valueFromAnimation(float newValue) override;

		T& operator*();

		T& operator->();

		AnimationVariable& operator=(const T& newValue);

		explicit operator T ();
	};
	using AnimationVariablef = AnimationVariable<float>;
	using AVariablef = AnimationVariable<float>;
	using AnimationVariablei = AnimationVariable<int>;
	using AVariablei = AnimationVariable<int>;

	template<typename T>
	bool convertPointer(const YAML::Node &node, AnimationVariable<T>*& animationUnit);
}

#include "animationVariable.inl"
