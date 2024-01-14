#include "Location.hpp"

orl::Option<ie::Location> ieml::Decode<char, ie::Location>::decode(ieml::Node const& node) {
	auto& str{node.get_raw().except().str};
	if(str == "origin") {
		return ie::Location::Origin;
	} else if(str == "center") {
		return ie::Location::Center;
	} else if(str == "end") {
		return ie::Location::End;
	}
	return {};
}
