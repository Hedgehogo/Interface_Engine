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
}

template<>
struct ieml::Decode<char, ie::Location2> {
	static orl::Option<ie::Location2> decode(ieml::Node const& node);
};
