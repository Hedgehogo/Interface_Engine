#include "yamlBuildExceptions.hpp"

namespace ui {
	BaseException::BaseException(std::string description) : description(std::move(description)) {}
	
	const char* BaseException::what() const noexcept { return description.c_str();}
	
	BaseYamlException::BaseYamlException(YAML::Mark mark, const std::string& description) :
		BaseException(std::to_string(mark.line) + std::string(", ") + std::to_string(mark.column) + description), mark(mark) {}
	
	YAML::Mark BaseYamlException::getMark() { return mark; }
	
	NonexistentTypeYamlException::NonexistentTypeYamlException(YAML::Mark mark, const std::string& type, const std::string &base) :
		BaseYamlException(mark, std::string("Type '") + type + std::string("' is not type '") + base + std::string("', maybe you forgot to add type '") + base + std::string("' to the list of child types of '") + type + std::string("'")),
		type(type), base(base) {}
	
	std::string NonexistentTypeYamlException::getType() { return type; }
	
	std::string NonexistentTypeYamlException::getBase() { return base; }
}
