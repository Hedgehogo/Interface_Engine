#include "Side.hpp"

orl::Option<ie::Side> ieml::Decode<char, ie::Side>::decode(ieml::Node const& node) {
	auto& str{node.get_raw().except().str};
	if(str == "up") {
		return ie::Side::Up;
	} else if(str == "down") {
		return ie::Side::Down;
	} else if(str == "right") {
		return ie::Side::Right;
	} else if(str == "left") {
		return ie::Side::Left;
	}
	return {};
}
