#include <yaml-cpp/yaml.h>
#include "load_modules.hpp"

#include "IE/modules/yaml-cpp/modules/load_c_modules/load_c_modules.hpp"

void ie::load_modules(int argc, char* argv[0], std::filesystem::path modules_list) {
	if(modules_list.empty())
		return;
	
	YAML::Node libs{YAML::LoadFile(modules_list.string())};
	
	load_c_modules(libs, argc, argv);
}
