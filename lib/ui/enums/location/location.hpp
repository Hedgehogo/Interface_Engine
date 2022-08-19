#pragma once
#include "../../../yaml/yamlWithSfml/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	enum class Location {
		origin,
		center,
		end
	};
	
	Location createLocationFromYaml(const YAML::Node &node);
}
