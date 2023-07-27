#pragma once

#include "../yaml.hpp"
#include "../../exception/baseException.hpp"

namespace ui {
	class BaseYamlException : public BaseException {
	public:
		BaseYamlException(YAML::Mark mark, const std::string& description);
		
		YAML::Mark getMark();
	
	protected:
		YAML::Mark mark;
	};
}
