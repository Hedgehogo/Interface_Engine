#pragma once

#include "../Location/Location.hpp"

namespace ie {
	enum class Location2 {
		UpLeft, Up, UpRight,
		Left, Center, Right,
		DownLeft, Down, DownRight
	};
	
	Location get_vertical_location(Location2 location2);
	
	Location get_horizontal_location(Location2 location2);
	
	Location2 make_location2(Location vertical, Location horizontal);
	
	/*old_yaml_decode
	template<>
	struct Decode<Location2> {
		static bool decode(const YAML::Node& node, Location2& location2);
	};
	*/
}
