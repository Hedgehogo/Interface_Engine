#include <iostream>
#include "../../../ui/animation/animator/unit/iAnimatorUnit.hpp"
#include "buffer.hpp"

namespace ui {
	std::map<std::string, std::vector<std::function<void(IAnimatorUnit*)>>> animatorUnitRequest;
	std::map<std::string, IAnimatorUnit*> animatorUnitBuffer;
	
	void animatorUnitRequestUpdate() {
		for(auto& requesters: animatorUnitRequest) {
			for(auto& requester: requesters.second) {
				requester(animatorUnitBuffer[requesters.first]);
			}
		}
	}
	
	void addNextAnimatorUnit(const YAML::Node& node, std::function<void(IAnimatorUnit*)> fun, std::string nameNextNode) {
		if(const YAML::Node& nextNode = node[nameNextNode]; nextNode && nextNode.IsScalar() && nextNode.as<std::string>() != "this") {
			animatorUnitRequest[nextNode.as<std::string>()].emplace_back(fun);
		} else if(const YAML::Node& nextsNode = node[nameNextNode + 's']; nextsNode) {
			for(auto& unit: nextsNode) {
				if(unit.IsScalar() && unit.as<std::string>() != "this") {
					animatorUnitRequest[unit.as<std::string>()].emplace_back(fun);
				}
			}
		}
	}
	
	void addUnitInBuffer(const YAML::Node& node, IAnimatorUnit* unit, std::string name) {
		if(const YAML::Node& nameNode = node[name]; nameNode)
			animatorUnitBuffer[nameNode.as<std::string>()] = unit;
		
	}
}
