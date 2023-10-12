#include "Corner.hpp"

namespace ie {
	bool Decode<Corner>::decode(const YAML::Node& node, Corner& corner) {
		std::string str{node.as<std::string>()};
		if(str == "up-right") {
			corner = Corner::UpRight;
		} else if(str == "up-left") {
			corner = Corner::UpLeft;
		} else if(str == "down-right") {
			corner = Corner::DownRight;
		} else if(str == "down-left") {
			corner = Corner::DownLeft;
		} else {
			throw YAML::BadConversion(node.Mark());
		}
		return true;
	}
}
