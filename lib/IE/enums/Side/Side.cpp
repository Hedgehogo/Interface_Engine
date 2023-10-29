#include "Side.hpp"

namespace ie {
	/*old_yaml_decode_impl
	bool Decode<Side>::decode(const YAML::Node& node, Side& side) {
		std::string str{node.as<std::string>()};
		if(str == "up") {
			side = Side::Up;
		} else if(str == "down") {
			side = Side::Down;
		} else if(str == "right") {
			side = Side::Right;
		} else if(str == "left") {
			side = Side::Left;
		} else {
			throw YAML::BadConversion(node.Mark());
		}
		return true;

	}
	*/
}
