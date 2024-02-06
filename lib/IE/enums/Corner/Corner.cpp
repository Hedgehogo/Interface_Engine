#include "Corner.hpp"

orl::Option<ie::Corner> ieml::Decode<char, ie::Corner>::decode(ieml::Node const& node) {
	auto& str{node.get_raw().except().str};
	if(str == "up-right") {
		return ie::Corner::UpRight;
	} else if(str == "up-left") {
		return ie::Corner::UpLeft;
	} else if(str == "down-right") {
		return ie::Corner::DownRight;
	} else if(str == "down-left") {
		return ie::Corner::DownLeft;
	}
	return {};
}
