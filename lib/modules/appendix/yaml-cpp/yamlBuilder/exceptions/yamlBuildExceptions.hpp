#pragma once
#include <string>
#include <exception>
#include <utility>
#include "../../yaml.hpp"

namespace ui {
	class BaseException : public std::exception {
	protected:
		std::string description;
	
	public:
		BaseException(std::string description);
	
		const char* what() const noexcept override;
	};
	
	class BaseYamlException : public BaseException {
	protected:
		YAML::Mark mark;
	
	public:
		BaseYamlException(YAML::Mark mark, const std::string& description);
		
		YAML::Mark getMark();
	};
	
	class NonexistentTypeYamlException : public BaseYamlException {
	protected:
		std::string type;
		std::string base;
		
	public:
		NonexistentTypeYamlException(YAML::Mark mark, const std::string& type, const std::string &base);
		
		std::string getType();
		
		std::string getBase();
	};
}
