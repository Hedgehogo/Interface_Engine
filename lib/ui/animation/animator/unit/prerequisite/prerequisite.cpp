#include "prerequisite.hpp"

namespace ui {
	Prerequisite::Prerequisite(IValve* valve, std::vector<IAnimatorUnit*> nextTrue, std::vector<IAnimatorUnit*> nextFalse) :
		nextTrue(nextTrue), nextFalse(nextFalse), valve(valve), nextTrueBuf(nextTrue), nextFalseBuf(nextFalse) {
		for(auto& unit: this->nextTrue) {
			if(!unit)
				unit = this;
		}
		
		for(auto& unit: this->nextFalse) {
			if(!unit)
				unit = this;
		}
	}
	
	void Prerequisite::setSpeed(PSfloat speed) {
		for(auto& unit: this->nextTrue) {
			if(unit != this)
				unit->setSpeed(speed);
		}
		
		for(auto& unit: this->nextFalse) {
			if(unit != this)
				unit->setSpeed(speed);
		}
	}
	
	void Prerequisite::restart() {
		for(auto& unit: this->nextTrue) {
			unit->restart();
		}
		
		for(auto& unit: this->nextFalse) {
			unit->restart();
		}
		
	}
	
	std::vector<IAnimatorUnit*> Prerequisite::update(float time) {
		return (*valve)() ? nextTrue : nextFalse;
	}
	
	void Prerequisite::addNextTrue(IAnimatorUnit* unit) {
		nextTrue.push_back(unit);
	}
	
	void Prerequisite::addNextFalse(IAnimatorUnit* unit) {
		nextFalse.push_back(unit);
	}
	
	IAnimatorUnit* Prerequisite::copy() {
		
		std::vector<IAnimatorUnit*> copyNextTrue{nextTrueBuf.size()};
		
		for(size_t i = 0; i < nextTrueBuf.size(); ++i) {
			copyNextTrue[i] = nextTrueBuf[i]->copy();
		}
		
		std::vector<IAnimatorUnit*> copyNextFalse{nextFalseBuf.size()};
		
		for(size_t i = 0; i < nextFalseBuf.size(); ++i) {
			copyNextFalse[i] = nextFalseBuf[i]->copy();
		}
		
		return new Prerequisite{valve->copy(), copyNextTrue, copyNextFalse};
	}
	
	Prerequisite::~Prerequisite() {
		for(auto item: nextTrueBuf) {
			delete item;
		}
		
		for(auto item: nextFalseBuf) {
			delete item;
		}
		
		delete valve;
	}
	
	
	bool DecodePointer<Prerequisite>::decodePointer(const YAML::Node& node, Prerequisite*& prerequisite) {
		prerequisite = new Prerequisite{
			node["valve"].as<IValve*>(),
			getAnimatorUnits(node, "next-true"),
			getAnimatorUnits(node, "next-false")
		};
		
		addNextAnimatorUnit(node, [=](IAnimatorUnit* unit) {
			prerequisite->addNextTrue(unit);
		}, "next-true");
		
		addNextAnimatorUnit(node, [=](IAnimatorUnit* unit) {
			prerequisite->addNextFalse(unit);
		}, "next-false");
		
		addUnitInBuffer(node, prerequisite);
		return true;
	}
}
