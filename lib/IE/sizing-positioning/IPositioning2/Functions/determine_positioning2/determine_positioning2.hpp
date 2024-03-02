#pragma once

#include "../../Positioning2/Positioning2.hpp"
#include "IE/ieml/shortcuts/shortcuts.hpp"

namespace ie {
	auto determine_positioning2(ieml::Node const& node) -> orl::Option<std::string>;
}