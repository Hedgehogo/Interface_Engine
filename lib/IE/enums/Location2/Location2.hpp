#pragma once

#include "../Location/Location.hpp"

namespace ie {
	enum class Location2 {
		UpLeft, Up, UpRight,
		Left, Center, Right,
		DownLeft, Down, DownRight
	};
	
	auto get_vertical_location(Location2 location2) -> Location;
	
	auto get_horizontal_location(Location2 location2) -> Location;
	
	auto make_location2(Location vertical, Location horizontal) -> Location2;
}

template<>
struct ieml::Decode<char, ie::Location2> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Location2>;
};
