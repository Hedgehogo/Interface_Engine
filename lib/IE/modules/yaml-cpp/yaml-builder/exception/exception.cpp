#include "exception.hpp"

namespace ie {
	NonexistentTypeYamlException::NonexistentTypeYamlException(YAML::Mark mark, const std::string& type, const std::string& base) :
		BaseYamlException(mark), type_(type), base_(base) {
	}
	
	std::string NonexistentTypeYamlException::get_description() const {
		return
			std::string("Type '") + type_ + std::string("' is not type '") + base_ + std::string("', maybe you forgot to add type '") +
			type_ + std::string("' to the list of child types of '") + base_ + std::string("'");
	}
	
	std::string NonexistentTypeYamlException::get_type() {
		return type_;
	}
	
	std::string NonexistentTypeYamlException::get_base() {
		return base_;
	}
	
	AbstractTypeYamlException::AbstractTypeYamlException(YAML::Mark mark, const std::string& type) :
		BaseYamlException(mark), type_(type) {
	}
	
	std::string AbstractTypeYamlException::get_description() const {
		return
			std::string("Type '") + type_ + std::string("' is abstract, it is impossible to create an object of type '") + type_ + std::string("'");
	}
	
	std::string AbstractTypeYamlException::get_type() {
		return type_;
	}
	
	FailedDetermineTypeYamlException::FailedDetermineTypeYamlException(YAML::Mark mark, const std::string& type) :
		BaseYamlException(mark), type_(type) {
	}
	
	std::string FailedDetermineTypeYamlException::get_description() const {
		return std::string("Failed to determine the type, expected type '") + type_ + std::string("'");
	}
	
	std::string FailedDetermineTypeYamlException::get_type() {
		return type_;
	}
}
