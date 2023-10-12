#pragma once

#include <yaml-cpp/yaml.h>

namespace ie {
	void loadCModules(const YAML::Node& libs, int argc = 0, char* argv[] = {});
}
