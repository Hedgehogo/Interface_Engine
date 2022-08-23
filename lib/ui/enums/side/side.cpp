#include "side.hpp"

namespace ui {
	Side createSideFromYaml(const YAML::Node &node) {
		std::string str{node.as<std::string>()};
		if(str == "up") {
			return Side::up;
		} else if(str == "down") {
			return Side::down;
		} else if(str == "right") {
			return Side::right;
		} else if(str == "left") {
			return Side::left;
		} else {
			throw YAML::BadConversion(node.Mark());
		}
	}
}
