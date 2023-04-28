#include "side.hpp"

namespace ui {
	
	
	bool Decode<Side>::decode(const YAML::Node& node, Side& side) {
		std::string str{node.as<std::string>()};
		if(str == "up") {
			side = Side::up;
		} else if(str == "down") {
			side = Side::down;
		} else if(str == "right") {
			side = Side::right;
		} else if(str == "left") {
			side = Side::left;
		} else {
			throw YAML::BadConversion(node.Mark());
		}
		return true;
	}
}
