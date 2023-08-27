#include "yamlBuildExceptions.hpp"

namespace ie {
	NonexistentTypeYamlException::NonexistentTypeYamlException(YAML::Mark mark, const std::string& type, const std::string& base) :
		BaseYamlException(mark, std::string("Type '") + type + std::string("' is not type '") + base + std::string("', maybe you forgot to add type '") + type + std::string("' to the list of child types of '") + base + std::string("'")),
		type(type), base(base) {
	}
	
	std::string NonexistentTypeYamlException::getType() {
		return type;
	}
	
	std::string NonexistentTypeYamlException::getBase() {
		return base;
	}
	
	AbstractTypeYamlException::AbstractTypeYamlException(YAML::Mark mark, const std::string& type) :
		BaseYamlException(mark, std::string("Type '") + type + std::string("' is abstract, it is impossible to create an object of type '") + type + std::string("'")),
		type(type) {
	}
	
	std::string AbstractTypeYamlException::getType() {
		return type;
	}
	
	FailedDetermineTypeYamlException::FailedDetermineTypeYamlException(YAML::Mark mark, const std::string& type) :
		BaseYamlException(mark, std::string("Failed to determine the type, expected type '") + type + std::string("'")),
		type(type) {
	}
	
	std::string FailedDetermineTypeYamlException::getType() {
		return type;
	}
}
