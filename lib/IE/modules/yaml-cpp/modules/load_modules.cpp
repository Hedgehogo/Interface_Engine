#include <yaml-cpp/yaml.h>
#include "load_modules.hpp"

#include "IE/modules/yaml-cpp/modules/load_c_modules/load_c_modules.hpp"

void ie::load_modules(int argc, char* argv[0], std::filesystem::path modulesList) {
	if(modulesList.empty())
		return;
	
	YAML::Node libs{YAML::LoadFile(modulesList.string())};
	
	load_c_modules(libs, argc, argv);
}
