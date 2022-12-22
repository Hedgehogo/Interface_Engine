#pragma once

#include <vector>
#include "../iAnimatorUnit.hpp"
#include "../../../variables/iAnimationVariable.hpp"
#include "../../../changeVariable/baseChangeVariable.hpp"
#include "../empty/emptyAnimatorUnit.hpp"

namespace ui {
	class AnimationUnit : public IAnimatorUnit{
	public:
		struct AnimationVariable{
			IAnimationVariable* animationVariable;
			std::vector<BaseChangeVariable*> changeVariables;
			float speed = 1;
			unsigned int activeChanger = 0;
			float timeStartChanger = 0;
		};

	protected:
		IAnimatorUnit* nextUnit;
		float startAnimation;
		std::vector<AnimationVariable> animationVariables;
		std::vector<AnimationVariable*> animationUpdatableVariables;
	public:

		explicit AnimationUnit(std::vector<AnimationVariable> animationVariables, IAnimatorUnit *nextUnit = new EmptyAnimatorUnit());

		void restart() override;

		IAnimatorUnit* update(float time) override;

		void setNextUnit(IAnimatorUnit *nextUnit);

		~AnimationUnit();
	};
} // ui