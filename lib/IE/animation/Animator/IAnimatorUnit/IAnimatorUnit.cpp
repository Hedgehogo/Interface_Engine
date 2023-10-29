#include "IAnimatorUnit.hpp"

namespace ie {
	/*old_yaml
	std::vector<IAnimatorUnit*> get_animator_units(const YAML::Node& node, std::string name_next_node) {
		std::vector<IAnimatorUnit*> result{};
		
		if(const YAML::Node& next_node = node[name_next_node]; next_node) {
			if(!next_node.IsScalar())
				result = {next_node.as<IAnimatorUnit*>()};
			else if(next_node.as<std::string>() == "this")
				result = {nullptr};
		} else if(const YAML::Node& nexts_node = node[name_next_node + 's']; nexts_node) {
			for(auto& unit: nexts_node) {
				if(!unit.IsScalar())
					result.push_back(unit.as<IAnimatorUnit*>());
				else if(unit.as<std::string>() == "this")
					result.push_back(nullptr);
			}
		}
		
		return result;
	}
	*/
}