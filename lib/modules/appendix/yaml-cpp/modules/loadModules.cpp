#include <yaml-cpp/yaml.h>
#include "loadModules.hpp"

#include "loadCModules/loadCModules.hpp"

void ui::loadModules(int argc, char** argv, std::filesystem::path modulesList) {
	if(modulesList.empty())
		return;
	
	YAML::Node libs{YAML::LoadFile(modulesList)};
	
	loadCModules(libs, argc, argv);
}
