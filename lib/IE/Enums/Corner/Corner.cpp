#include "Corner.hpp"

namespace ui {
	bool Decode<Corner>::decode(const YAML::Node& node, Corner& corner) {
		std::string str{node.as<std::string>()};
		if(str == "up-right") {
			corner = Corner::upRight;
		} else if(str == "up-left") {
			corner = Corner::upLeft;
		} else if(str == "down-right") {
			corner = Corner::downRight;
		} else if(str == "down-left") {
			corner = Corner::downLeft;
		} else {
			throw YAML::BadConversion(node.Mark());
		}
		return true;
	}
}
