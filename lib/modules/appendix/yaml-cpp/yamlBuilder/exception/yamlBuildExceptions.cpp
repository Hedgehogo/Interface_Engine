#include "yamlBuildExceptions.hpp"

namespace ui {
	NonexistentTypeYamlException::NonexistentTypeYamlException(YAML::Mark mark, const std::string& type, const std::string &base) :
		BaseYamlException(mark, std::string("Type '") + type + std::string("' is not type '") + base + std::string("', maybe you forgot to add type '") + type + std::string("' to the list of child types of '") + base + std::string("'")),
		type(type), base(base) {}
	
	std::string NonexistentTypeYamlException::getType() { return type; }
	
	std::string NonexistentTypeYamlException::getBase() { return base; }
}
