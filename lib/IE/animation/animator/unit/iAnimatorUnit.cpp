#include "iAnimatorUnit.hpp"

namespace ui {
	std::vector<IAnimatorUnit*> getAnimatorUnits(const YAML::Node& node, std::string nameNextNode) {
		std::vector<IAnimatorUnit*> result{};
		
		if(const YAML::Node& nextNode = node[nameNextNode]; nextNode) {
			if(!nextNode.IsScalar())
				result = {nextNode.as<IAnimatorUnit*>()};
			else if(nextNode.as<std::string>() == "this")
				result = {nullptr};
		} else if(const YAML::Node& nextsNode = node[nameNextNode + 's']; nextsNode) {
			for(auto& unit: nextsNode) {
				if(!unit.IsScalar())
					result.push_back(unit.as<IAnimatorUnit*>());
				else if(unit.as<std::string>() == "this")
					result.push_back(nullptr);
			}
		}
		
		return result;
	}
}