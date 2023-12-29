#pragma once

#include "../../exception/BaseYamlException.hpp"

namespace ie {
	class NonexistentTypeYamlException : public BaseYamlException {
	public:
		NonexistentTypeYamlException(YAML::Mark mark, const std::string& type, const std::string& base);
		
		std::string get_type();
		
		std::string get_base();
	
	protected:
		std::string type_;
		std::string base_;
	};
	
	class AbstractTypeYamlException : public BaseYamlException {
	public:
		AbstractTypeYamlException(YAML::Mark mark, const std::string& type);
		
		std::string get_type();
	
	protected:
		std::string type_;
	};
	
	class FailedDetermineTypeYamlException : public BaseYamlException {
	public:
		FailedDetermineTypeYamlException(YAML::Mark mark, const std::string& type);
		
		std::string get_type();
	
	protected:
		std::string type_;
	};
}
