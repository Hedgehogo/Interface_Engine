#include "animationUnit.hpp"

namespace ui {
	AnimationUnit::Variable::Variable(IAnimationVariable *animationVariable, std::vector<BaseChangeVariable *> changeVariables) : animationVariable(animationVariable), changeVariables(changeVariables) {}

	AnimationUnit::AnimationUnit(std::vector<Variable> animationVariables, IAnimatorUnit *nextUnit) :
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
		for (int i = 0; i < animationUpdatableVariables.size(); ++i){
			Variable*& animationVariable = animationUpdatableVariables[i];

			if (animationVariable->timeStartChanger == 0) animationVariable->timeStartChanger = time;

			float timeFromChanger = time - (animationVariable->timeStartChanger);
			BaseChangeVariable * changeVariable = animationVariable->changeVariables[animationVariable->activeChanger];

			if (changeVariable->getSize() < timeFromChanger){
				animationVariable->activeChanger++;
				if (animationVariable->activeChanger == animationVariable->changeVariables.size()){
					animationUpdatableVariables.erase(std::vector<Variable*>::iterator{&animationVariable});
					i--;
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

	template<>
	bool convert(const YAML::Node &node, AnimationUnit::Variable& animationVar){
		animationVar = AnimationUnit::Variable{
			animationVariablesBuffer[node["var"].as<std::string>()],
			node["change-variable"] ? std::vector<BaseChangeVariable*>{node["change-variable"].as<BaseChangeVariable*>()} : node["change-variables"].as<std::vector<BaseChangeVariable*>>()
		};
		return true;
	}

	bool convertPointer(const YAML::Node &node, AnimationUnit*& animationUnit){

		IAnimatorUnit* nextUnit{nullptr};

		if(node["next"]){
			if(!node["next"].IsScalar()){
				nextUnit = node["next"].as<IAnimatorUnit *>();
			}
		}else{
			nextUnit = new EmptyAnimatorUnit();
		}

		animationUnit = new AnimationUnit{
			node["var"] ? std::vector<AnimationUnit::Variable>{node["var"].as<AnimationUnit::Variable>()} : node["vars"].as<std::vector<AnimationUnit::Variable>>(),
			nextUnit
		};

		if (node["next"] && node["next"].IsScalar() && node["next"].as<std::string>() != "this"){
			animatorUnitRequest[node["next"].as<std::string>()].push_back(animationUnit);
		}

		if (node["name"]) animatorUnitBuffer[node["name"].as<std::string>()] = animationUnit;

		return true;
	}
}