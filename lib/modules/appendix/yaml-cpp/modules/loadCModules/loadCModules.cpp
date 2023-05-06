#include "loadCModules.hpp"

#include <openLib/openLib.hpp>
#include <yaml-cpp/yaml.h>

namespace ui {
	void loadCModules(std::filesystem::path modulesList, int argc, char *argv[]){
		if (modulesList.empty()) return;
		YAML::Node CLibs{YAML::LoadFile(modulesList)["CLib"]};
		
		if (!CLibs) return;
		
		if (auto paths = CLibs["path"]; paths){
			for(const auto& path: paths){
				openLib::DynamicLibrary dl{path.as<std::string>()};
				dl.getSim<void(*)(int argc, char *argv[])>("init")(argc, argv);
			}
		}
	}
}