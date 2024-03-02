#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	enum class Location {
		Origin,
		Center,
		End
	};
}

template<>
struct ieml::Decode<char, ie::Location> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Location>;
};
