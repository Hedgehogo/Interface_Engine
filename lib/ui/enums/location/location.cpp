#include "location.hpp"

namespace ui {
	Location createLocationFromYaml(const YAML::Node &node) {
		std::string str{node.as<std::string>()};
		if(str == "origin") {
			return Location::origin;
		} else if(str == "center") {
			return Location::center;
		} else if(str == "end") {
			return Location::end;
		} else {
			throw YAML::BadConversion{node.Mark()};
		}
	}
}
