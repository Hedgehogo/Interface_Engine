#include "animator.hpp"

#include <memory>

namespace ui {
	Animator::Animator(std::vector<IAnimatorUnit*> units, PSfloat speed) : units(units), unitsBuff(units) {
		for(auto& unit: units) {
			unit->setSpeed(speed);
		}
	}
	
	void replace(std::vector<IAnimatorUnit*>& mainVec, std::vector<IAnimatorUnit*>::iterator iter, std::vector<IAnimatorUnit*> vec) {
		if(vec.empty()) {
			mainVec.erase(iter);
			return;
		} else if(vec.size() == 1 && vec[0] == *iter)
			return;
		
		
		bool erase = vec[0] == *iter;
		if(!erase)
			mainVec.erase(iter);
		
		mainVec.insert(iter + (int)erase, vec.begin(), vec.end());
	}
	
	void Animator::update(float time) {
		for(size_t i = 0; i < units.size(); ++i) {
			std::vector<IAnimatorUnit*> addUnits{units[i]->update(time)};
			replace(units, units.begin() + i, addUnits);
			i += addUnits.size() - 1;
		}
		
		std::vector<IAnimatorUnit*> buf;
		for(auto unit = units.rbegin(); unit != units.rend(); ++unit) {
			if(std::find(buf.begin(), buf.end(), *unit) == buf.end())
				buf.push_back(*unit);
		}
		
		units = {buf.rbegin(), buf.rend()};
	}
	
	Animator* Animator::copy() {
		std::vector<IAnimatorUnit*> copyUnits{unitsBuff.size()};
		for(size_t i = 0; i < unitsBuff.size(); ++i) {
			copyUnits[i] = unitsBuff[i]->copy();
		}
		return new Animator{copyUnits};
	}
	
	Animator::~Animator() {
		for(auto& unit: unitsBuff) {
			delete unit;
		}
	}
	
	
	bool DecodePointer<Animator>::decodePointer(const YAML::Node& node, Animator*& animator) {
		animator = new Animator{
			node["unit"] ? std::vector<IAnimatorUnit*>{node["unit"].as<IAnimatorUnit*>()} : node["units"].as<std::vector<IAnimatorUnit*>>(),
			(node["speed"] ? Buffer::get<Sfloat>(node["speed"]) : std::make_shared<Sfloat>(1))
		};
		return true;
	}
}