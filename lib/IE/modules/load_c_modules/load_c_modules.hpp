#pragma once

#include <IEML/node.hpp>

namespace ie {
	auto load_c_modules(ieml::Node const& libs, int argc = 0, char* argv[0] = {}) -> void;
}
