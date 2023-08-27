#include "Animation.hpp"

#include <utility>
#include <iostream>

namespace ie {
	Animation::Variable::Variable(PSfloat animationVariable, std::vector<IChangeVariable*> changeVariables) : animationVariable(std::move(animationVariable)), changeVariables(std::move(changeVariables)) {
	}
	
	Animation::Variable Animation::Variable::copy() {
		std::vector<IChangeVariable*> copyChangeVariables{changeVariables.size()};
		
		for(size_t i = 0; i < copyChangeVariables.size(); ++i) {
			copyChangeVariables[i] = changeVariables[i]->copy();
		}
		
		return {animationVariable, copyChangeVariables};
	}
	
	Animation::Animation(std::vector<Variable> animationVariables, PSfloat speed, std::vector<IAnimatorUnit*> nextUnits) :
		nextUnits(nextUnits), nextUnitsBuff(nextUnits), animationVariables(std::move(animationVariables)), speed(std::move(speed)) {
		for(auto& unit: this->nextUnits) {
			if(!unit)
				unit = this;
		}
		
		restart();
	}
	
	void Animation::setSpeed(PSfloat speed) {
		if(!this->speed)
			this->speed = speed;
		
		for(auto& unit: nextUnits) {
			if(unit != this)
				unit->setSpeed(speed);
		}
	}
	
	void Animation::restart() {
		animationUpdatableVariables.resize(animationVariables.size());
		
		for(std::size_t i = 0; i < animationUpdatableVariables.size(); ++i) {
			animationUpdatableVariables[i] = &animationVariables[i];
		}
		
		for(auto& animationVariable: animationVariables) {
			animationVariable.activeChanger = 0;
			animationVariable.timeStartChanger = 0;
		}
	}
	
	std::vector<IAnimatorUnit*> Animation::update(float time) {
		for(std::size_t i = 0; i < animationUpdatableVariables.size(); ++i) {
			Variable*& animationVariable = animationUpdatableVariables[i];
			
			if(animationVariable->timeStartChanger == 0 || time < animationVariable->timeStartChanger)
				animationVariable->timeStartChanger = time;
			
			float timeFromChanger = time - (animationVariable->timeStartChanger);
			IChangeVariable* changeVariable = animationVariable->changeVariables[animationVariable->activeChanger];
			
			timeFromChanger *= speed->getValue();
			animationVariable->animationVariable->setValue((*changeVariable)(timeFromChanger));
			
			if(changeVariable->getSize() < timeFromChanger) {
				animationVariable->activeChanger++;
				if(animationVariable->activeChanger == animationVariable->changeVariables.size()) {
					animationUpdatableVariables.erase(std::vector<Variable*>::iterator{&animationVariable});
					--i;
					continue;
				}
				animationVariable->timeStartChanger = time;
				changeVariable = animationVariable->changeVariables[animationVariable->activeChanger];
			}
		}
		
		if(animationUpdatableVariables.empty()) {
			restart();
			return nextUnits;
		}
		
		return {this};
	}
	
	void Animation::setNextUnits(std::vector<IAnimatorUnit*> nextUnits) {
		this->nextUnits = nextUnits;
	}
	
	void Animation::addNextUnits(IAnimatorUnit* nextUnit) {
		nextUnits.push_back(nextUnit);
	}
	
	Animation* Animation::copy() {
		std::vector<IAnimatorUnit*> copyNextUnits{nextUnitsBuff.size()};
		
		for(size_t i = 0; i < nextUnitsBuff.size(); ++i) {
			copyNextUnits[i] = nextUnitsBuff[i]->copy();
		}
		
		return new Animation{animationVariables, speed, copyNextUnits};
	}
	
	Animation::~Animation() {
		for(auto& item: nextUnitsBuff) {
			if(item)
				delete item;
		}
	}
	
	bool Decode<Animation::Variable>::decode(const YAML::Node& node, Animation::Variable& animationVar) {
		animationVar = Animation::Variable{
			Buffer::get<Sfloat>(node["var"]),
			node["change-variable"] ? std::vector<IChangeVariable*>{node["change-variable"].as<IChangeVariable*>()} : node["change-variables"].as<std::vector<IChangeVariable*>>()
		};
		return true;
	}
	
	bool DecodePointer<Animation>::decodePointer(const YAML::Node& node, Animation*& animation) {
		animation = new Animation{
			node["var"] ? std::vector<Animation::Variable>{node["var"].as<Animation::Variable>()} : node["vars"].as<std::vector<Animation::Variable>>(),
			(node["speed"] ? Buffer::get<Sfloat>(node["speed"]) : PSfloat{nullptr}),
			getAnimatorUnits(node)
		};
		
		addNextAnimatorUnit(node, [=](IAnimatorUnit* unit) {
			animation->addNextUnits(unit);
		});
		
		addUnitInBuffer(node, animation);
		return true;
	}
}