#include "location.hpp"

namespace ui {
	template<>
	bool convert(const YAML::Node &node, Location &location) {
		std::string str{node.as<std::string>()};
		if(str == "origin") {
			location = Location::origin;
		} else if(str == "center") {
			location = Location::center;
		} else if(str == "end") {
			location = Location::end;
		} else {
			throw YAML::BadConversion{node.Mark()};
		}
		return true;
	}
}
