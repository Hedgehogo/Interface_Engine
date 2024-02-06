#pragma once

#include "IE/ieml/shortcuts/shortcuts.hpp"

namespace ie {
	orl::Option<std::string> determine_sizing(ieml::Node const& node);
}