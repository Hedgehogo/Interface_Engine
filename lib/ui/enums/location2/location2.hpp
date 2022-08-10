#pragma once
#include "../location/location.hpp"

namespace ui {
	enum class Location2 {
		  upLeft,     up,   upRight,
		    left, center,     right,
		downLeft,   down, downRight
	};
	
	Location getVerticalLocation(Location2 location2);
	
	Location getHorizontalLocation(Location2 location2);
	
	Location2 createLocation2(Location vertical, Location horizontal);
	
	Location2 createLocation2FromYaml(const YAML::Node &node);
}
