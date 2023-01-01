#include "animation.hpp"
#include "../../../exception/notExistAnimationVariable.hpp"

namespace ui {
	Animation::Variable::Variable(IAnimationVariable *animationVariable, std::vector<BaseChangeVariable *> changeVariables) : animationVariable(animationVariable), changeVariables(changeVariables) {}

	Animation::Animation(std::vector<Variable> animationVariables, std::vector<IAnimatorUnit*> nextUnits) :
		animationVariables(animationVariables), nextUnits(nextUnits), nextUnitsBuff(nextUnits){
		for (auto &unit: this->nextUnits){
			if(!unit) unit = this;
		}

		for (auto unit = std::find(nextUnitsBuff.begin(), nextUnitsBuff.end(), nullptr); unit != nextUnitsBuff.end(); unit = std::find(nextUnitsBuff.begin(), nextUnitsBuff.end(), nullptr)){
			nextUnitsBuff.erase(unit);
		}

		restart();
	}

	void Animation::restart() {
		animationUpdatableVariables.resize(animationVariables.size());

		for(int i = 0; i < animationUpdatableVariables.size(); ++i) {
			animationUpdatableVariables[i] = &animationVariables[i];
		}

		for (auto &animationVariable: animationVariables){
			animationVariable.activeChanger = 0;
			animationVariable.timeStartChanger = 0;
		}
	}

	std::vector<IAnimatorUnit*> Animation::update(float time) {
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
			return nextUnits;
		}

		return {this};
	}

	Animation::~Animation() {
		for (auto &item: nextUnitsBuff){
			delete item;
		}
	}
	void Animation::setNextUnits(std::vector<IAnimatorUnit*> nextUnits) {
		this->nextUnits = nextUnits;
	}

	void Animation::addNextUnits(IAnimatorUnit *nextUnit) {
		nextUnits.push_back(nextUnit);
	}

	template<>
	bool convert(const YAML::Node &node, Animation::Variable& animationVar){
		IAnimationVariable *animationVariable;

		if (node["var"].IsScalar()){
			auto nameVar = node["var"].as<std::string>();
			if (animationVariablesBuffer.find(nameVar) == animationVariablesBuffer.end())
				throw NotExistAnimationVariable(nameVar);
			animationVariable = animationVariablesBuffer[nameVar];
		}else{
			animationVariable = node["var"].as<IAnimationVariable*>();
		}

		animationVar = Animation::Variable{
			animationVariable,
			node["change-variable"] ? std::vector<BaseChangeVariable*>{node["change-variable"].as<BaseChangeVariable*>()} : node["change-variables"].as<std::vector<BaseChangeVariable*>>()
		};
		return true;
	}

	bool convertPointer(const YAML::Node &node, Animation*& animation){

		std::vector<IAnimatorUnit*> nextUnits{};

		if(node["next"]){
			if(!node["next"].IsScalar())
				nextUnits = {node["next"].as<IAnimatorUnit *>()};
			else if (node["next"].as<std::string>() == "this")
				nextUnits = {nullptr};
		} else if(node["nexts"]){
			for (auto& unit : node["nexts"]){
				if(!unit.IsScalar())
					nextUnits.push_back(unit.as<IAnimatorUnit*>());
				else if (unit.as<std::string>() == "this")
					nextUnits.push_back(nullptr);
			}
		}

		animation = new Animation{
			node["var"] ? std::vector<Animation::Variable>{node["var"].as<Animation::Variable>()} : node["vars"].as<std::vector<Animation::Variable>>(),
			nextUnits
		};

		if (node["next"] && node["next"].IsScalar() && node["next"].as<std::string>() != "this") {
			animatorUnitRequest[node["next"].as<std::string>()].push_back(animation);
		} else if(node["nexts"]){
			for (auto& unit : node["nexts"]){
				if(unit.IsScalar() && unit.as<std::string>() != "this")
					animatorUnitRequest[unit.as<std::string>()].push_back(animation);
			}
		}

		if (node["name"]) animatorUnitBuffer[node["name"].as<std::string>()] = animation;

		return true;
	}
}