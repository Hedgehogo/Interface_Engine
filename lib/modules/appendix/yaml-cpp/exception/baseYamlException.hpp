#pragma once

#include "../yaml.hpp"
#include "../../exception/baseException.hpp"

namespace ui {
	class BaseYamlException : public BaseException {
	protected:
		YAML::Mark mark;
	
	public:
		BaseYamlException(YAML::Mark mark, const std::string& description);
		
		YAML::Mark getMark();
	};
}
