#pragma once

#include "../yaml.hpp"
#include "../../exception/BaseException.hpp"

namespace ie {
	class BaseYamlException : public BaseException {
	public:
		BaseYamlException(YAML::Mark mark);
		
		std::string get_note() const override;
		
		YAML::Mark get_mark() const;
	
	protected:
		YAML::Mark mark_;
	};
}
