#include "animator.hpp"

namespace ui {
	Animator::Animator(std::vector<IAnimatorUnit*> units) : units(units), unitsBuff(units) {}

	void replace(std::vector<IAnimatorUnit*>& mainVec, std::vector<IAnimatorUnit*>::iterator iter, std::vector<IAnimatorUnit*> vec){
		if (vec.empty()){
			mainVec.erase(iter);
			return;
		} else if(vec.size() == 1 && vec[0] == *iter) return;


		bool erase = vec[0] == *iter;
		if(!erase)mainVec.erase(iter);

		mainVec.insert(iter + (int)erase , vec.begin(), vec.end());
	}

	void Animator::update(float time) {
		for (size_t i = 0; i != units.size(); ++i) {
			std::vector<IAnimatorUnit*> addUnits{units[i]->update(time)};
			replace(units, units.begin() + i, addUnits);
			i += addUnits.size() - 1;
		}

		std::vector<IAnimatorUnit*> buf;
		for (auto unit = units.rbegin(); unit != units.rend(); ++unit) {
			if (std::find(buf.begin(), buf.end(), *unit) == buf.end())
				buf.push_back(*unit);
		}

		units = buf;
	}

	Animator *Animator::copy() {
		return new Animator{units};
	}

	Animator::~Animator() {
		for (auto &unit: unitsBuff){
			delete unit;
		}
	}

	bool convertPointer(const YAML::Node &node, Animator*& animator){
		animator = new Animator{
			node["unit"] ? std::vector<IAnimatorUnit*> {node["unit"].as<IAnimatorUnit *>()} : node["units"].as<std::vector<IAnimatorUnit*>>()
		};
		return true;
	}
} // ui