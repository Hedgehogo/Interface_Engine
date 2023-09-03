#include "Location.hpp"

namespace ie {
	bool Decode<Location>::decode(const YAML::Node& node, Location& location) {
		std::string str{node.as<std::string>()};
		if(str == "origin") {
			location = Location::Origin;
		} else if(str == "center") {
			location = Location::Center;
		} else if(str == "end") {
			location = Location::End;
		} else {
			throw YAML::BadConversion{node.Mark()};
		}
		return true;
	}
}
