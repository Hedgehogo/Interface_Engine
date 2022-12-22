#include "animationUnit.hpp"

namespace ui {
	AnimationUnit::AnimationUnit(std::vector<AnimationVariable> animationVariables, IAnimatorUnit *nextUnit) :
		animationVariables(animationVariables), nextUnit(nextUnit ? nextUnit : this){
		restart();
	}

	void AnimationUnit::restart() {
		animationUpdatableVariables.resize(animationVariables.size());

		for(int i = 0; i < animationUpdatableVariables.size(); ++i) {
			animationUpdatableVariables[i] = &animationVariables[i];
		}

		for (auto &animationVariable: animationVariables){
			animationVariable.activeChanger = 0;
			animationVariable.timeStartChanger = 0;
		}
	}

	IAnimatorUnit* AnimationUnit::update(float time) {
		for (auto &animationVariable : animationUpdatableVariables) {
			if (animationVariable->timeStartChanger == 0) animationVariable->timeStartChanger = time;

			float timeFromChanger = time - (animationVariable->timeStartChanger);
			BaseChangeVariable * changeVariable = animationVariable->changeVariables[animationVariable->activeChanger];

			if (changeVariable->getSize() < timeFromChanger){
				animationVariable->activeChanger++;
				if (animationVariable->activeChanger == animationVariable->changeVariables.size()){
					animationUpdatableVariables.erase(std::vector<AnimationVariable*>::iterator{&animationVariable});
					continue;
				}
				animationVariable->timeStartChanger = time;
				changeVariable = animationVariable->changeVariables[animationVariable->activeChanger];
			}

			animationVariable->animationVariable->valueFromAnimation((*changeVariable)(timeFromChanger));
		}

		if (animationUpdatableVariables.empty()){
			restart();
			return nextUnit;
		}

		return this;
	}

	AnimationUnit::~AnimationUnit() {
		std::destroy(animationVariables.begin(), animationVariables.end());
		delete nextUnit;
	}

	void AnimationUnit::setNextUnit(IAnimatorUnit *nextUnit) {
		AnimationUnit::nextUnit = nextUnit;
	}
}