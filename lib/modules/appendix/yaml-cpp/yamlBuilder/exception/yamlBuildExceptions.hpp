#pragma once

#include "../../exception/baseYamlException.hpp"

namespace ui {
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
