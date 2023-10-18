#include "exception.hpp"

namespace ie {
	NonexistentTypeYamlException::NonexistentTypeYamlException(YAML::Mark mark, const std::string& type, const std::string& base) :
		BaseYamlException(mark, std::string("Type '") + type + std::string("' is not type '") + base + std::string("', maybe you forgot to add type '") + type + std::string("' to the list of child types of '") + base + std::string("'")),
		type(type), base(base) {
	}
	
	std::string NonexistentTypeYamlException::get_type() {
		return type;
	}
	
	std::string NonexistentTypeYamlException::get_base() {
		return base;
	}
	
	AbstractTypeYamlException::AbstractTypeYamlException(YAML::Mark mark, const std::string& type) :
		BaseYamlException(mark, std::string("Type '") + type + std::string("' is abstract, it is impossible to create an object of type '") + type + std::string("'")),
		type(type) {
	}
	
	std::string AbstractTypeYamlException::get_type() {
		return type;
	}
	
	FailedDetermineTypeYamlException::FailedDetermineTypeYamlException(YAML::Mark mark, const std::string& type) :
		BaseYamlException(mark, std::string("Failed to determine the type, expected type '") + type + std::string("'")),
		type(type) {
	}
	
	std::string FailedDetermineTypeYamlException::get_type() {
		return type;
	}
}
