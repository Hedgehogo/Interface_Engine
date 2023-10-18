#include "Animator.hpp"

#include <memory>

namespace ie {
	Animator::Animator(std::vector<IAnimatorUnit*> units, PSfloat speed) : units(units), units_buff(units) {
		for(auto& unit: units) {
			unit->set_speed(speed);
		}
	}
	
	void replace(std::vector<IAnimatorUnit*>& main_vec, std::vector<IAnimatorUnit*>::iterator iter, std::vector<IAnimatorUnit*> vec) {
		if(vec.empty()) {
			main_vec.erase(iter);
			return;
		} else if(vec.size() == 1 && vec[0] == *iter)
			return;
		
		
		bool erase = vec[0] == *iter;
		if(!erase)
			main_vec.erase(iter);
		
		main_vec.insert(iter + (int)erase, vec.begin(), vec.end());
	}
	
	void Animator::update(float time) {
		for(size_t i = 0; i < units.size(); ++i) {
			std::vector<IAnimatorUnit*> add_units{units[i]->update(time)};
			replace(units, units.begin() + i, add_units);
			i += add_units.size() - 1;
		}
		
		std::vector<IAnimatorUnit*> buf;
		for(auto unit = units.rbegin(); unit != units.rend(); ++unit) {
			if(std::find(buf.begin(), buf.end(), *unit) == buf.end())
				buf.push_back(*unit);
		}
		
		units = {buf.rbegin(), buf.rend()};
	}
	
	Animator* Animator::copy() {
		std::vector<IAnimatorUnit*> copy_units{units_buff.size()};
		for(size_t i = 0; i < units_buff.size(); ++i) {
			copy_units[i] = units_buff[i]->copy();
		}
		return new Animator{copy_units};
	}
	
	Animator::~Animator() {
		for(auto& unit: units_buff) {
			delete unit;
		}
	}
	
	bool DecodePointer<Animator>::decode_pointer(const YAML::Node& node, Animator*& animator) {
		animator = new Animator{
			node["unit"] ? std::vector<IAnimatorUnit*>{node["unit"].as<IAnimatorUnit*>()} : node["units"].as<std::vector<IAnimatorUnit*>>(),
			(node["speed"] ? Buffer::get<Sfloat>(node["speed"]) : std::make_shared<Sfloat>(1))
		};
		return true;
	}
}