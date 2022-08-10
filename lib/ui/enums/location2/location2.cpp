#include "location2.hpp"

namespace ui {
	Location getVerticalLocation(Location2 location2) {
		switch(location2) {
			case Location2::upLeft:
			case Location2::up:
			case Location2::upRight:
				return Location::origin;
				break;
			case Location2::left:
			case Location2::center:
			case Location2::right:
				return Location::center;
				break;
			case Location2::downLeft:
			case Location2::down:
			case Location2::downRight:
				return Location::end;
				break;
		}
        return Location::center;
	}
	
	Location getHorizontalLocation(Location2 location2) {
		switch(location2) {
			case Location2::upLeft:
			case Location2::left:
			case Location2::downLeft:
				return Location::origin;
				break;
			case Location2::up:
			case Location2::center:
			case Location2::down:
				return Location::center;
				break;
			case Location2::upRight:
			case Location2::right:
			case Location2::downRight:
				return Location::end;
				break;
		}
        return Location::center;
	}
	
	Location2 createLocation2(Location vertical, Location horizontal) {
		switch(vertical) {
			case Location::origin:
				switch(horizontal) {
					case Location::origin:
						return Location2::upLeft;
						break;
					case Location::center:
						return Location2::up;
						break;
					case Location::end:
						return Location2::upRight;
						break;
				}
				break;
			case Location::center:
				switch(horizontal) {
					case Location::origin:
						return Location2::left;
						break;
					case Location::center:
						return Location2::center;
						break;
					case Location::end:
						return Location2::right;
						break;
				}
				break;
			case Location::end:
				switch(horizontal) {
					case Location::origin:
						return Location2::downLeft;
						break;
					case Location::center:
						return Location2::down;
						break;
					case Location::end:
						return Location2::downRight;
						break;
				}
				break;
		}
        return Location2::center;
	}
	
	Location2 createLocation2FromYaml(const YAML::Node &node) {
		try{
			std::string str{node.as<std::string>()};
			
			if(str == "up-left") {
				return Location2::upLeft;
			} else if(str == "up") {
				return Location2::up;
			} else if(str == "up-right") {
				return Location2::upRight;
			} else if(str == "left") {
				return Location2::left;
			} else if(str == "center") {
				return Location2::center;
			} else if(str == "right") {
				return Location2::right;
			} else if(str == "down-left") {
				return Location2::downLeft;
			} else if(str == "down") {
				return Location2::down;
			} else if(str == "down-right") {
				return Location2::downRight;
			} else {
				throw YAML::BadConversion{node.Mark()};
			}
		} catch(YAML::BadConversion& e) {
			return createLocation2(createLocationFromYaml(node["vertical"]), createLocationFromYaml(node["horizontal"]));
		}
	}
}