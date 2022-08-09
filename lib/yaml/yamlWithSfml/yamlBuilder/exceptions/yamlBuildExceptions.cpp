#include "yamlBuildExceptions.hpp"

namespace ui {
	const char *AbstractTypeYamlException::what() const throw() {
		return "The 'createFromYaml' function returned 'nullptr', maybe you tried to yaml to create an instance of an abstract class";
	}
	
	NonexistentTypeYamlException::NonexistentTypeYamlException(std::string type) : type(std::move(type)) {}
	
	const char *NonexistentTypeYamlException::what() const throw() {
		return (std::string("A type '") + type + std::string("' was requested, but it is not in the list, perhaps it is not a descendant of a readable type or, if it is your own type, you may have forgotten to add it to the list")).c_str();
	}
}
