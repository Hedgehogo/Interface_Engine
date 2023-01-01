#pragma once

#include <vector>
#include "../iAnimatorUnit.hpp"
#include "../../../variables/iAnimationVariable.hpp"
#include "../../../changeVariable/baseChangeVariable.hpp"
#include "../empty/emptyAnimatorUnit.hpp"

namespace ui {
	class Animation : public IAnimatorUnit{
	public:
		struct Variable{
			IAnimationVariable* animationVariable;
			std::vector<BaseChangeVariable*> changeVariables;
			unsigned int activeChanger = 0;
			float timeStartChanger = 0;

			Variable(IAnimationVariable *animationVariable = nullptr, std::vector<BaseChangeVariable *> changeVariables = {});
		};

	protected:
		std::vector<IAnimatorUnit*> nextUnits;
		std::vector<IAnimatorUnit*> nextUnitsBuff;
		std::vector<Variable> animationVariables;
		std::vector<Variable*> animationUpdatableVariables;
		float speed;

	public:
		explicit Animation(std::vector<Variable> animationVariables, std::vector<IAnimatorUnit *> nextUnits = {}, float speed = 1);

		void restart() override;

		std::vector<IAnimatorUnit*> update(float time) override;

		void setNextUnits(std::vector<IAnimatorUnit*> nextUnit) override;

		void addNextUnits(IAnimatorUnit* nextUnit) override;

		~Animation();
	};

	template<>
	bool convert(const YAML::Node &node, Animation::Variable& animationUnit);

	bool convertPointer(const YAML::Node &node, Animation*& animation);
} // ui