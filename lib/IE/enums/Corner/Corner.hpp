#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	enum class Corner {
		UpRight,
		UpLeft,
		DownRight,
		DownLeft
	};
}

template<>
struct ieml::Decode<char, ie::Corner> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Corner>;
};
