#include "Location2.hpp"

namespace ie {
	Location get_vertical_location(Location2 location2) {
		switch(location2) {
			case Location2::UpLeft:
			case Location2::Up:
			case Location2::UpRight:
				return Location::Origin;
			case Location2::Left:
			case Location2::Center:
			case Location2::Right:
				return Location::Center;
			case Location2::DownLeft:
			case Location2::Down:
			case Location2::DownRight:
				return Location::End;
		}
		return Location::Center;
	}
	
	Location get_horizontal_location(Location2 location2) {
		switch(location2) {
			case Location2::UpLeft:
			case Location2::Left:
			case Location2::DownLeft:
				return Location::Origin;
			case Location2::Up:
			case Location2::Center:
			case Location2::Down:
				return Location::Center;
			case Location2::UpRight:
			case Location2::Right:
			case Location2::DownRight:
				return Location::End;
		}
		return Location::Center;
	}
	
	Location2 make_location2(Location vertical, Location horizontal) {
		switch(vertical) {
			case Location::Origin:
				switch(horizontal) {
					case Location::Origin:
						return Location2::UpLeft;
					case Location::Center:
						return Location2::Up;
					case Location::End:
						return Location2::UpRight;
				}
				break;
			case Location::Center:
				switch(horizontal) {
					case Location::Origin:
						return Location2::Left;
					case Location::Center:
						return Location2::Center;
					case Location::End:
						return Location2::Right;
				}
				break;
			case Location::End:
				switch(horizontal) {
					case Location::Origin:
						return Location2::DownLeft;
					case Location::Center:
						return Location2::Down;
					case Location::End:
						return Location2::DownRight;
				}
				break;
		}
		return Location2::Center;
	}
}

orl::Option<ie::Location2> ieml::Decode<char, ie::Location2>::decode(ieml::Node const& node) {
	for(auto map: node.get_map_view().ok_or_none()) {
		return ie::make_location2(
			map.at("vertical").except().as<ie::Location>().except(),
			map.at("horizontal").except().as<ie::Location>().except()
		);
	}
	auto& str{node.get_raw().except().str};
	if(str == "up-left") {
		return ie::Location2::UpLeft;
	} else if(str == "up") {
		return ie::Location2::Up;
	} else if(str == "up-right") {
		return ie::Location2::UpRight;
	} else if(str == "left") {
		return ie::Location2::Left;
	} else if(str == "center") {
		return ie::Location2::Center;
	} else if(str == "right") {
		return ie::Location2::Right;
	} else if(str == "down-left") {
		return ie::Location2::DownLeft;
	} else if(str == "down") {
		return ie::Location2::Down;
	} else if(str == "down-right") {
		return ie::Location2::DownRight;
	}
	return {};
}