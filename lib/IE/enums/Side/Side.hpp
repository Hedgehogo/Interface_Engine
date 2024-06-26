#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	enum class Side {
		Up,
		Down,
		Right,
		Left
	};
}

template<>
struct ieml::Decode<char, ie::Side> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Side>;
};
