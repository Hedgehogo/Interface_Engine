#pragma once

#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"
#include <functional>

namespace ie {
	class AnimationManager;
	
	class IAnimatorUnit;
	
	extern std::map<std::string, std::vector<std::function<void(IAnimatorUnit*)>>> animator_unit_request;
	extern std::map<std::string, IAnimatorUnit*> animator_unit_buffer;
	
	void animator_unit_request_update();
	
	void add_next_animator_unit(const YAML::Node& node, std::function<void(IAnimatorUnit*)> fun, std::string name_next_node = "next");
	
	void add_unit_in_buffer(const YAML::Node& node, IAnimatorUnit* unit, std::string name = "name");
}
