#pragma once

#include "../yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui{

	class AnimationManager;
	class IAnimatorUnit;
	class IAnimationVariable;

	extern std::map<std::string, IAnimationVariable*> animationVariablesBuffer;
	extern std::map<std::string, std::vector<IAnimatorUnit*>> animatorUnitRequest;
	extern std::map<std::string, IAnimatorUnit*> animatorUnitBuffer;

	void animatorUnitRequestUpdate();
}
