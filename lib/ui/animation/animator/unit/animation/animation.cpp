#include "animation.hpp"

#include <utility>
#include "../../../exception/notExistAnimationVariable.hpp"


namespace ui {
	Animation::Variable::Variable(PSfloat animationVariable, std::vector<IChangeVariable *> changeVariables) : animationVariable(std::move(animationVariable)), changeVariables(std::move(changeVariables)) {}

	Animation::Variable Animation::Variable::copy() {
		std::vector<IChangeVariable *> copyChangeVariables{changeVariables.size()};

		for (size_t i = 0; i < copyChangeVariables.size(); ++i) {
			copyChangeVariables[i] = changeVariables[i]->copy();
		}

		return {animationVariable, copyChangeVariables};
	}

	Animation::Animation(std::vector<Variable> animationVariables, std::vector<IAnimatorUnit *> nextUnits, float speed) :
		animationVariables(std::move(animationVariables)), nextUnits(nextUnits), nextUnitsBuff(nextUnits), speed(speed){
		for (auto &unit: this->nextUnits){
			if(!unit) unit = this;
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
		time *= speed;
		for (int i = 0; i < animationUpdatableVariables.size(); ++i){
			Variable*& animationVariable = animationUpdatableVariables[i];

			if (animationVariable->timeStartChanger == 0) animationVariable->timeStartChanger = time;

			float timeFromChanger = time - (animationVariable->timeStartChanger);
			IChangeVariable * changeVariable = animationVariable->changeVariables[animationVariable->activeChanger];

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

			animationVariable->animationVariable->setValue((*changeVariable)(timeFromChanger));
		}

		if (animationUpdatableVariables.empty()){
			restart();
			return nextUnits;
		}

		return {this};
	}

	void Animation::setNextUnits(std::vector<IAnimatorUnit*> nextUnits) {
		this->nextUnits = nextUnits;
	}
	void Animation::addNextUnits(IAnimatorUnit *nextUnit) {
		nextUnits.push_back(nextUnit);
	}

	Animation* Animation::copy() {
		std::vector<IAnimatorUnit*> copyNextUnits{nextUnitsBuff.size()};

		for (size_t i = 0; i < nextUnitsBuff.size(); ++i) {
			copyNextUnits[i] = nextUnitsBuff[i]->copy();
		}

		return new Animation{animationVariables, copyNextUnits, speed};
	}

	Animation::~Animation() {
		for (auto &item: nextUnitsBuff){
			if (item) delete item;
		}
	}

	template<>
	bool convert(const YAML::Node &node, Animation::Variable& animationVar){
		animationVar = Animation::Variable{
			Buffer::get<Sfloat>(node["var"]),
			node["change-variable"] ? std::vector<IChangeVariable*>{node["change-variable"].as<IChangeVariable*>()} : node["change-variables"].as<std::vector<IChangeVariable*>>()
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
			nextUnits,
			convDef(node["speed"], 1.f)
		};

		if (node["next"] && node["next"].IsScalar() && node["next"].as<std::string>() != "this") {
			animatorUnitRequest[node["next"].as<std::string>()].emplace_back([=](IAnimatorUnit *unit){animation->addNextUnits(unit);});
		} else if(node["nexts"]){
			for (auto& unit : node["nexts"]){
				if(unit.IsScalar() && unit.as<std::string>() != "this")
					animatorUnitRequest[unit.as<std::string>()].emplace_back([=](IAnimatorUnit *unit){animation->addNextUnits(unit);});
			}
		}

		if (node["name"]) animatorUnitBuffer[node["name"].as<std::string>()] = animation;

		return true;
	}
}