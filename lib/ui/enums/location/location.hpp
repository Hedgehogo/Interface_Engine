#pragma once
#include "../../../yaml/yamlWithSfml/yaml.hpp"

namespace ui {
	enum class Location {
		origin,
		center,
		end
	};
	
	template<>
	bool convert(const YAML::Node &node, Location &location);
	
	Location createLocationFromYaml(const YAML::Node &node);
}
