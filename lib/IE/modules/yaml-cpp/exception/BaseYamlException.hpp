#pragma once

#include "../yaml.hpp"
#include "../../exception/BaseException.hpp"

namespace ie {
	class BaseYamlException : public BaseException {
	public:
		BaseYamlException(YAML::Mark mark, const std::string& description);
		
		YAML::Mark getMark();
	
	protected:
		YAML::Mark mark;
	};
}
