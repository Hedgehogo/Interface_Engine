#pragma once

#include <yaml-cpp/yaml.h>

namespace ie {
	auto load_c_modules(const YAML::Node& libs, int argc = 0, char* argv[0] = {}) -> void;
}
