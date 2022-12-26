#pragma once

#include <vector>
#include "../iAnimatorUnit.hpp"
#include "../../../variables/iAnimationVariable.hpp"
#include "../../../changeVariable/baseChangeVariable.hpp"
#include "../empty/emptyAnimatorUnit.hpp"

namespace ui {
	class AnimationUnit : public IAnimatorUnit{
	public:
		struct Variable{
			IAnimationVariable* animationVariable;
			std::vector<BaseChangeVariable*> changeVariables;
			unsigned int activeChanger = 0;
			float timeStartChanger = 0;

			Variable(IAnimationVariable *animationVariable = nullptr, std::vector<BaseChangeVariable *> changeVariables = {});
		};

	protected:
		IAnimatorUnit* nextUnit;
		float startAnimation;
		std::vector<Variable> animationVariables;
		std::vector<Variable*> animationUpdatableVariables;
	public:

		explicit AnimationUnit(std::vector<Variable> animationVariables, IAnimatorUnit *nextUnit = new EmptyAnimatorUnit());

		void restart() override;

		IAnimatorUnit* update(float time) override;

		void setNextUnit(IAnimatorUnit *nextUnit) override;

		~AnimationUnit();
	};

	template<>
	bool convert(const YAML::Node &node, AnimationUnit::Variable& animationUnit);

	bool convertPointer(const YAML::Node &node, AnimationUnit*& animationUnit);
} // ui