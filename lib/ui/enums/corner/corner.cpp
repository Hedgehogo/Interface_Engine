#include "corner.hpp"

namespace ui {
	Corner createCornerFromYaml(const YAML::Node &node) {
		std::string str{node.as<std::string>()};
		if(str == "up-right") {
			return Corner::upRight;
		} else if(str == "up-left") {
			return Corner::upLeft;
		} else if(str == "down-right") {
			return Corner::downRight;
		} else if(str == "down-left") {
			return Corner::downLeft;
		} else {
			throw YAML::BadConversion(node.Mark());
		}
	}
}
