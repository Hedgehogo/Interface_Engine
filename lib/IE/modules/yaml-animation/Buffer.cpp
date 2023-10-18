#include <iostream>
#include "IE/animation/Animator/IAnimatorUnit/IAnimatorUnit.hpp"
#include "Buffer.hpp"

namespace ie {
	std::map<std::string, std::vector<std::function<void(IAnimatorUnit*)>>> animator_unit_request;
	std::map<std::string, IAnimatorUnit*> animator_unit_buffer;
	
	void animator_unit_request_update() {
		for(auto& requesters: animator_unit_request) {
			for(auto& requester: requesters.second) {
				requester(animator_unit_buffer[requesters.first]);
			}
		}
	}
	
	void add_next_animator_unit(const YAML::Node& node, std::function<void(IAnimatorUnit*)> fun, std::string name_next_node) {
		if(const YAML::Node& next_node = node[name_next_node]; next_node && next_node.IsScalar() && next_node.as<std::string>() != "this") {
			animator_unit_request[next_node.as<std::string>()].emplace_back(fun);
		} else if(const YAML::Node& nexts_node = node[name_next_node + 's']; nexts_node) {
			for(auto& unit: nexts_node) {
				if(unit.IsScalar() && unit.as<std::string>() != "this") {
					animator_unit_request[unit.as<std::string>()].emplace_back(fun);
				}
			}
		}
	}
	
	void add_unit_in_buffer(const YAML::Node& node, IAnimatorUnit* unit, std::string name) {
		if(const YAML::Node& name_node = node[name]; name_node)
			animator_unit_buffer[name_node.as<std::string>()] = unit;
		
	}
}